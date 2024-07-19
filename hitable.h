#ifndef HITABLE_H
#define HITABLE_H

#include "Vec3.h"
#include "ray.h"
#include <memory>

class Material;

struct hit_info{
    bool hit;
    Vec3 hit_point;
    Vec3 normal;
    double t;
    std::shared_ptr<Material> material;
    hit_info(): hit(false) {};
};

class Hitable {
public:
    virtual ~Hitable(){};
    virtual hit_info find_hit(Ray& ray, double low_t, double high_t) = 0;
};

#endif