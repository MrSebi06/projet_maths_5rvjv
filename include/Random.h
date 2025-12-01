//
// Created by Sebastian on 21/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_RANDOM_H
#define PROJET_MATHS_5RVJV_RANDOM_H
#include <random>

class Random {
    inline static std::random_device rd;
    inline static auto gen = std::mt19937(rd());

public:
    static std::uniform_real_distribution<float> float_dist(const float min, const float max) {
        return std::uniform_real_distribution(min, max);
    }


    static float get_float(std::uniform_real_distribution<float> dist) {
        return dist(gen);
    }
};


#endif //PROJET_MATHS_5RVJV_RANDOM_H
