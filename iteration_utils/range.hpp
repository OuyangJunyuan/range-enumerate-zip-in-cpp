namespace it_utils {
    using namespace std;
    /***
     * debug:比直接for慢1倍,release下慢0.1倍
     * @tparam T
     * @param b
     * @param e
     * @param s
     * @return
     */
    template<typename T=std::size_t>
    constexpr auto range(T b, T e, double s = 1.0) {
        struct range_wrapper {
            struct iterator {
                T &current_;
                T &step_;

                bool inline operator!=(const iterator &other) const { return current_ != other.current_; }

                void inline operator++() {
                    current_ += step_;
                }

                auto inline operator*() const { return current_; }
            };

            explicit range_wrapper(T _begin, T _end, T _step) :
                    begin_(_begin),
                    end_(_end),
                    step_(_step) {};

            auto inline begin() { return iterator{begin_, step_}; }

            auto inline end() { return iterator{end_, step_}; }

            T begin_, end_, step_;
        };
        return range_wrapper{b, e, b < e ? (T) s : -(T) s};
    }
}
