//
// Created by mateo on 20.8.22.
//

#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "utils.h"
#include "ray.h"

class camera {
public:
   
    camera(
            point3 lookfrom,
            point3 lookat,
            glm::vec3   vup,
            float vfov, // vertical field-of-view in degrees
            float aspect_ratio,
            float aperture,
            float focus_dist
        );

    [[nodiscard]]
    ray get_ray(float u, float v) const;


private:
    point3 origin = point3(0, 0, 0);
    point3 lower_left_corner = point3(0, 0, 0);
    glm::vec3 horizontal = glm::vec3(0, 0, 0);
    glm::vec3 vertical  = glm::vec3(0, 0, 0);
    glm::vec3 u, v, w;
    float lens_radius;
};


#endif //PROJECT_CAMERA_H
