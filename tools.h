//
// Created by ou on 2021/7/11.
//

#ifndef TEST_TOOLS_H
#define TEST_TOOLS_H

/***
 *
 * @tparam split
 * @tparam T
 * @param head
 */

//#define CLOSE
template<char split = ',', class T>
inline void comma(T head) {
#ifndef CLOSE
    std::cout << head << std::endl;
#endif
}

template<char split = ',', class T, class ...Args>
inline void comma(T head, Args... rest) {
#ifndef CLOSE
    if constexpr (sizeof...(rest) == 0)
        std::cout << head << std::endl;
    else {
        std::cout << head << split;
        comma<split>(rest...);
    }
#endif
}

/***
 *
 * @tparam T
 * @return
 */
template<typename T>
T I___________________________I(T) ;
template<typename T>
T I___________________________I() ;
#define TEST(T)   I___________________________I(T)


/***
 *
 */




#endif //TEST_TOOLS_H
