//
// Created by mateo on 09.10.22..
//

#include "box.h"
#include "aarect.h"

box::box(const point3& p0, const point3& p1) {
    this->box_min = p0;
    this->box_max = p1;

    sides.add(make_shared<xy_rect>(p0.x, p1.x, p0.y, p1.y, p1.z));
    sides.add(make_shared<xy_rect>(p0.x, p1.x, p0.y, p1.y, p0.z));

    sides.add(make_shared<xz_rect>(p0.x, p1.x, p0.z, p1.z, p1.y));
    sides.add(make_shared<xz_rect>(p0.x, p1.x, p0.z, p1.z, p0.y));

    sides.add(make_shared<yz_rect>(p0.y, p1.y, p0.z, p1.z, p1.x));
    sides.add(make_shared<yz_rect>(p0.y, p1.y, p0.z, p1.z, p0.x));
}

bool box::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    return sides.hit(r, t_min, t_max, rec);
}