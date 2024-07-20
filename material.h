#ifndef MATERIAL_H 
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"
#include "Color.h"


Vec3 random_reflection_direction(Vec3 sphere_normal){
    Vec3 random_reflection_dir = random_unit_vector();
    while (dot(sphere_normal, random_reflection_dir) < 0.0){
        random_reflection_dir = random_unit_vector();
    }
    return random_reflection_dir;
}

class Material{
public:
    Color albedo;
    Material(Color albedo): albedo(albedo){};

    virtual ~Material() = default;

    virtual Ray scatter(Ray& input_ray, hit_info& hit_information) = 0;
    
    Color get_albedo(){
        return albedo;
    }

};

class Lambertian: public Material {
    public:

    Lambertian(Color albedo): Material(albedo) {};

    Ray scatter(Ray& input_ray, hit_info& hit_information) override {
        Vec3 reflected_direction = hit_information.normal + random_reflection_direction(hit_information.normal);
        if (reflected_direction.close_to_zero()){
            reflected_direction = hit_information.normal;
        }
        return Ray(hit_information.hit_point, reflected_direction);
    };
};

class Metal: public Material {
    public:

    Metal(Color albedo): Material(albedo) {};

    Ray scatter(Ray& input_ray, hit_info& hit_information) override {
        Vec3 reflected_direction = reflect(input_ray.direction(), hit_information.normal);
        return Ray(hit_information.hit_point, reflected_direction);
    };
};

#endif