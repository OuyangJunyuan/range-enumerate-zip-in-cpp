//
// Created by ou on 2021/7/10.
//

#ifndef TEST_ENUMERATE_HPP
#define TEST_ENUMERATE_HPP

#include <iostream>

/***
 *
 * @tparam T
 * @tparam iter_t
 * @param iterable
 * @return
 */
namespace it_utils {

    template<typename Container, typename F>
    void __enum_imp(Container &&c, F &&f) {
        std::size_t i = -1;
        using value_type = typename std::iterator_traits<decltype(std::begin(c))>::value_type;
        for (auto &&x : std::forward<Container>(c)) {
            f(++i, x);
        }
    }

#define enum(v, i, data, statement)  __enum_imp(v,[&](const auto & i, data) statement)
#define enum_i(v, data, statement)  __enum_imp(v,[&](const auto & i, data) statement)


    template<typename iter_t>
    struct enum_data {

        enum_data(std::size_t _i, iter_t _iter) : i(_i), iter(_iter), iter_obj(*iter) {}

        enum_data(const enum_data &_data) : i(_data.i), iter_obj(*_data.iter), copy(true) {}

        template<size_t I>
        inline decltype(auto) get() {
            if constexpr (I == 0) return i;
            else if constexpr (I == 1) return copy ? iter_obj : *iter;
        }

        template<size_t I>
        inline decltype(auto) get() const { return const_cast<enum_data *>(this)->template get<I>(); }

        std::size_t i;
        iter_t iter;
        typename std::iterator_traits<iter_t>::value_type iter_obj;
        bool copy = false;
    };


    template<typename container_t>
    struct enumerate {
    private:
        container_t &container_;
        using iter_t = decltype(std::begin(container_));
    private:
        enum_data<iter_t> result{0, std::begin(container_)};

        struct iter_wrapper {
            inline bool operator!=(const iter_t &other) const { return data_.iter != other; }

            inline void operator++() {
                ++data_.i;
                ++data_.iter;
            }

            inline auto &operator*() const { return data_; }

            enum_data<iter_t> &data_;
        } begin_it{result};

    public:
        explicit enumerate(container_t &_container) : container_(_container) {}

        explicit enumerate(container_t &&_container) : container_(_container) {}

        auto &begin() { return begin_it; }

        iter_t end() { return std::end(container_); }
    };

}

namespace std {
    using namespace it_utils;
    template<typename T>
    struct tuple_size<enum_data<T>> : integral_constant<std::size_t, 2> {
    };
    template<typename T>
    struct tuple_element<0, enum_data<T>> {
        using type = std::size_t;
    };
    template<typename T>
    struct tuple_element<1, enum_data<T>> {
        using type = typename std::iterator_traits<T>::value_type;
    };

}


#endif //TEST_ENUMERATE_HPP
