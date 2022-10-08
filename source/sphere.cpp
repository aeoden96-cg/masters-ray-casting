//
// Created by mateo on 28.7.22.
//

#include "sphere.h"
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = 2.0*dot(oc, r.direction())/2.0;
    auto c = dot(oc, oc) - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outward_normal = (rec.p - center) / (float)radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}