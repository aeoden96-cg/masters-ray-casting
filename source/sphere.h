//
// Created by mateo on 28.7.22.
//

#ifndef PROJECT_SPHERE_H
#define PROJECT_SPHERE_H

#include "hittable_list.h"


class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;
    double radius;
};




#endif //PROJECT_SPHERE_H
