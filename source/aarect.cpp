//
// Created by mateo on 09.10.22..
//

#include "aarect.h"

bool xy_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k-r.origin().z) / r.direction().z;
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x + t*r.direction().x;
    auto y = r.origin().y + t*r.direction().y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.t = t;
    auto outward_normal = glm::vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);

    rec.p = r.at(t);
    return true;
}

bool xz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k-r.origin().y) / r.direction().y;
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x + t*r.direction().x;
    auto z = r.origin().z + t*r.direction().z;
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.t = t;
    auto outward_normal = glm::vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);

    rec.p = r.at(t);
    return true;
}

bool yz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k-r.origin().x) / r.direction().x;
    if (t < t_min || t > t_max)
        return false;
    auto y = r.origin().y + t*r.direction().y;
    auto z = r.origin().z + t*r.direction().z;
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.t = t;
    auto outward_normal = glm::vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);

    rec.p = r.at(t);
    return true;
}