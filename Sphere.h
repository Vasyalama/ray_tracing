#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "material.h"
#include <memory>

class Sphere: public Hitable {
public:
    double radius;
    Vec3 center;
    std::shared_ptr<Material> material;

    Sphere(){
        center = {0,0,0};
        radius = 1.0;
    }

    Sphere(double r, Vec3 c, std::shared_ptr<Material> mat): radius(r), center(c), material(mat) {};

    hit_info find_hit(Ray& ray, double low_t, double high_t) override {
        hit_info result;
        Vec3 diff = center - ray.start();
        double a = ray.direction().length_squared();
        double b = -dot(ray.direction(), diff);
        double c = diff.length_squared() - radius * radius;

        double discriminant = b * b - a * c;
        if (discriminant < 0){
            result.hit = false;
            return result;
        }
        
        double sqrt_disc = std::sqrt(discriminant);
        double t1 = (-b + sqrt_disc)/a;
        double t2 = (-b - sqrt_disc)/a;

        double t;
        if (t1 <= low_t && t2 <= low_t){
            result.hit = false;
            return result;
        }
        else if (t1 > low_t && t2 <= low_t){
            t = t1;
        }
        else if (t1 <= low_t && t2 > low_t){
            t = t2;
        }
        else {
            t = std::min(t1, t2);
        }

        if (t > high_t){
            result.hit = false;
            return result;
        }

        result.hit = true;
        result.t = t;
        result.hit_point = ray.at(t);
        result.normal = unit_vect(result.hit_point - center);
        result.material = material;
        return result;
    }
};

#endif