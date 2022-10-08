#ifndef PROJECT_RAY_H
#define PROJECT_RAY_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color

class ray {
public:
    ray() {}
    ray(const point3& origin, const glm::vec3& direction)
            : orig(origin), dir(direction)
    {}

    point3 origin() const  { return orig; }
    glm::vec3 direction() const { return dir; }

    point3 at(double t) const {
        return orig + (float)t*dir;
    }

public:
    point3 orig;
    glm::vec3 dir;
};

#endif //PROJECT_RAY_H
