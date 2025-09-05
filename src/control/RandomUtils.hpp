#include <cstdlib>
#pragma once
class RandomUtils {
    public:

    /**
     * Get a random integer between min and max.
     */
    static int get_random_int(int min, int max) {
        return rand() % (max - min + 1) + min;
    }
};