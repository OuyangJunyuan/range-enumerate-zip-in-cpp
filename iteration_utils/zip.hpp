//
// Created by ou on 2021/7/13.
//

#ifndef TEST_ZIP_HPP
#define TEST_ZIP_HPP

#include <tuple>

#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define _ZIP_MAX_NUM 4
#define DEFINE_TN(_, n, __) T## n & t##n;
// 模板定义
template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(_ZIP_MAX_NUM, class T, void)>
struct TupleLike {
    BOOST_PP_REPEAT(_ZIP_MAX_NUM, DEFINE_TN, T)
};

// 偏特化模板定义
#define GEN_PARTIAL_SPECIALIZATION(N)   template<BOOST_PP_ENUM_PARAMS(N, typename T)> \
                                        struct TupleLike<BOOST_PP_ENUM_PARAMS(N, T)> {\
                                            BOOST_PP_REPEAT(N, DEFINE_TN, T)};

#define GEN_F(_, n, __)                 GEN_PARTIAL_SPECIALIZATION(BOOST_PP_ADD(n,1))
BOOST_PP_REPEAT (BOOST_PP_SUB(_ZIP_MAX_NUM, 1), GEN_F, _)


namespace it_utils {

    template<typename... Containers>
    struct zip {
    private:
        std::tuple<Containers &...> t;
        static const std::size_t N = sizeof...(Containers);
        static_assert(N <= _ZIP_MAX_NUM,
                      "zip(args...) : too much arguments(please modified the MACRO named \"_ZIP_MAX_NUM\" ");
        static const std::make_index_sequence<N> Ind;
        static const std::make_index_sequence<_ZIP_MAX_NUM - N> Ind_ret;

    private:
        template<std::size_t I>
        using fill_void = void;
        template<std::size_t ...I>
        using IndSeq = std::index_sequence<I...>;
        template<std::size_t I>
        using iter_type = decltype(std::begin(std::get<I>(t)));
        template<std::size_t I>
        using traits = std::iterator_traits<decltype(std::begin(std::get<I>(t)))>;
        template<std::size_t I>
        using pointer = typename traits<I>::pointer;
        template<std::size_t I>
        using value_type = typename traits<I>::value_type;

        template<std::size_t... I, typename T, typename TIT>
        inline static auto init_it_pointer(T &&t, TIT &&it, IndSeq<I...>) {
            ((it[I] = &*std::begin(std::get<I>(t))), ...);
        }

        template<std::size_t... I, typename T>
        constexpr inline static void next_one(T &&t, IndSeq<I...>) {
            ((t[I] = static_cast<pointer<I>>(t[I]) + 1), ...);
        }

        template<class T, std::size_t ...I, std::size_t ...N>

        constexpr inline static auto make_return(T &&t, IndSeq<I...>, IndSeq<N...>) {
            return TupleLike<value_type<I>..., fill_void<N>...>{*pointer<I>(t[I])...};
        }

    private:
        struct Iterator {
            void *p_container_element[N];

            inline bool operator!=(const iter_type<0> &other) { return p_container_element[0] != other.base(); }

            inline void operator++() { next_one(p_container_element, Ind); }

            inline decltype(auto) operator*() const { return make_return(p_container_element, Ind, Ind_ret); }
        } it;

    public:
        explicit zip(Containers &... args) : t(std::tie(args...)) {
            init_it_pointer(t, it.p_container_element, Ind);
        }

        auto &&begin() { return it; }

        auto end() { return std::end(std::get<0>(t)); }
    };

}
#undef GEN_F
#undef DEFINE_TN
#undef GEN_PARTIAL_SPECIALIZATION
#endif //TEST_ZIP_HPP
