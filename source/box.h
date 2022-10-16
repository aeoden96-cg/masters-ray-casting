//
// Created by mateo on 09.10.22..
//

#ifndef PROJECT_BOX_H
#define PROJECT_BOX_H

#include "utils.h"
#include "hittable_list.h"

class box : public hittable  {
public:
    box(const point3& p0, const point3& p1);
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


public:
    point3 box_min{};
    point3 box_max{};
    hittable_list sides;
};

#endif //PROJECT_BOX_H
