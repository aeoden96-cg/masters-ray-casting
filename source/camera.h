//
// Created by mateo on 20.8.22.
//

#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "rtweekend.h"
#include "ray.h"

class camera {
public:
    camera();

    [[nodiscard]]
    ray get_ray(float u, float v) const;


private:
    point3 origin = point3(0, 0, 0);
    point3 lower_left_corner = point3(0, 0, 0);
    glm::vec3 horizontal = glm::vec3(0, 0, 0);
    glm::vec3 vertical  = glm::vec3(0, 0, 0);
};


#endif //PROJECT_CAMERA_H
