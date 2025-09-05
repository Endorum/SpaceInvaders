#include <cstdlib>
#pragma once
class RandomUtils {
    public:

    static int get_random_int(int min, int max) {
        return rand() % (max - min + 1) + min;
    }
};