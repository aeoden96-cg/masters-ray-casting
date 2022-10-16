//
// Created by mateo on 28.7.22.
//

#ifndef PROJECT_RTWEEKEND_H
#define PROJECT_RTWEEKEND_H

// Common Headers
#include <iostream>
#include <memory>

// Math Headers
#include <cmath>
#include <limits>
#include <cstdlib>
#include <random>

// OpenGL Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Type aliases for vec3

using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

double degrees_to_radians(double degrees);
double clamp(double x, double min, double max);

//Random number generation

double random_double();
double random_double_modern_cpp();
double random_double(double min, double max);
static glm::vec3 random_vec3();
static glm::vec3 random_vec3(double min, double max);
glm::vec3 random_in_unit_sphere();
glm::vec3 random_unit_vector();
glm::vec3 random_in_hemisphere(const glm::vec3& normal);


#endif //PROJECT_RTWEEKEND_H
