//
// Created by mateo on 09.10.22..
//

#ifndef PROJECT_AARECT_H
#define PROJECT_AARECT_H

#include "hittable.h"
#include "utils.h"

class xy_rect : public hittable {
public:


    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k)
            : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


public:
    double x0, x1, y0, y1, k;
};


class xz_rect : public hittable {
public:


    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k)
            : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


public:
    double x0, x1, z0, z1, k;
};

class yz_rect : public hittable {
public:
    yz_rect() {}

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k)
            : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k){};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


public:
    double y0, y1, z0, z1, k;
};

#endif //PROJECT_AARECT_H
