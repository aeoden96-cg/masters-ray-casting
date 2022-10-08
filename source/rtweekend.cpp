//
// Created by mateo on 21.8.22.
//
#include "rtweekend.h"

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double random_double_modern_cpp() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

static glm::vec3 random_vec3() {
    return {random_double(), random_double(), random_double()};
}

static glm::vec3 random_vec3(double min, double max) {
    return {random_double(min,max), random_double(min,max), random_double(min,max)};
}


glm::vec3 random_in_unit_sphere() {
    while (true) {
        glm::vec3 p = random_vec3(-1,1);
        if (glm::dot(p,p) >= 1) continue;
        return p;
    }
}

glm::vec3 random_unit_vector() {
    //unit vector in glm
    return glm::normalize(random_in_unit_sphere());
}

glm::vec3 random_in_hemisphere(const glm::vec3& normal) {
    glm::vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}