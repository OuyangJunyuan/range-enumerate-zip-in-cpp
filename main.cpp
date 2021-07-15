#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <iteration_utils/iteration_utils.hpp>
#include "tools.h"

using namespace std;
using namespace it_utils;
#define N 1e7

int main() {
    {
        vector v1(1e7, 1), v2(v1), v3(v1);
        auto t1 = chrono::high_resolution_clock::now();
        comma(&v1[0], &v2[0], &v3[0]);
        cout << "---" << endl;
        for (auto[e1, e2, e3]:zip(v1, v2, v3)) {

        }
        auto t2 = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << endl << "---" << endl;
    }

    return 0;
}
