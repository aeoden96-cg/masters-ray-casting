//
// Created by mateo on 20.8.22.
//

#include "camera.h"

camera::camera() {
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    origin = point3(0, 0, 0);
    horizontal = glm::vec3(viewport_width, 0.0, 0.0);
    vertical = glm::vec3(0.0, viewport_height, 0.0);
    lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - glm::vec3(0, 0, focal_length);

}

ray camera::get_ray(float u, float v) const {
    return {origin, lower_left_corner + u * horizontal + v*vertical - origin};

}