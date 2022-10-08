//
// Created by mateo on 28.7.22.
//

#ifndef PROJECT_HITTABLE_H
#define PROJECT_HITTABLE_H
#include "ray.h"

using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color

struct hit_record {
    point3 p;
    glm::vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const glm::vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif //PROJECT_HITTABLE_H
