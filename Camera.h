#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "ray.h"
#include "Color.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Hitable.h"



class Camera{
public:
    const double DIFFUSE_CONSTANT = 0.5;
    double ray_depth = 10;
    Vec3 camera_center = {0,0,0};
    double aspect_ratio = 16.0/9.0;
    int image_height = 200;
    int image_width; 

    double viewport_height = 2.0;
    double viewport_width;
    double focal_length = 1.0;
    Vec3 viewport_delta_x;
    Vec3 viewport_delta_y;
    Vec3 viewport_top_left;
    Vec3 start_pixel;

    // antialiasing
    int sample_count = 100;



    HittableList scene;
    
    Camera(){
        setup();
    }

    void setup(){
        std::shared_ptr<Lambertian> mat1 = std::make_shared<Lambertian>(Color(0.9, 0.1, 0.1));
        std::shared_ptr<Lambertian> mat2 = std::make_shared<Lambertian>(Color(0.1, 0.1, 0.7));
        std::shared_ptr<Metal> metal= std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
        std::shared_ptr<Metal> metal2= std::make_shared<Metal>(Color(0.3, 0.8, 0.3));

        scene.push_back(std::make_shared<Sphere>(0.5, Vec3{0.0,0.0,1.0}, mat1));
        scene.push_back(std::make_shared<Sphere>(100.0, Vec3{0.0,-100.5, 1.0}, mat2));
        scene.push_back(std::make_shared<Sphere>(0.5, Vec3{1.0, 0.0, 1.0}, metal));
        scene.push_back(std::make_shared<Sphere>(0.5, Vec3{-1.0, 0.0, 1.0}, metal2));
        image_width = (int)(double(image_height) * aspect_ratio); 
        viewport_width = viewport_height * (double(image_width) / double(image_height));
        viewport_delta_x = {viewport_width/double(image_width), 0.0, 0.0};
        viewport_delta_y = {0.0, -viewport_height/double(image_height), 0.0};
        viewport_top_left = {-viewport_width/2, viewport_height/2, focal_length};
        //start_pixel = viewport_top_left + 0.5 * viewport_delta_x + 0.5 * viewport_delta_y;
    }

    void render(){
        std::cout << "P3" << std::endl;
        std::cout << image_width << " " << image_height << std::endl << "255" << std::endl;
        for (int i = 0; i < image_height; i++){
            std::clog << "\rScanlines remaining: " << (image_height - i) << std::flush;
            for (int j = 0; j < image_width; j++){
                Vec3 current_pixel_top_left = viewport_top_left + i * viewport_delta_y + j * viewport_delta_x;
                Color pixel_color= Color();
                for (int k = 0; k < sample_count; k++){
                    Vec3 rand_vector = viewport_delta_x * random_double() + viewport_delta_y * random_double();
                    Vec3 current_sample = current_pixel_top_left + rand_vector;
                    Ray ray(camera_center, current_sample);
                    pixel_color += cast_sample_ray(ray, ray_depth);
                }    
                pixel_color /= sample_count;
                pixel_color.write_to_ppm(std::cout);
            }
        }
        std::clog << "\rDone.                     \n";
    }

    

    Color cast_sample_ray(Ray& r, double ray_depth){
        if (ray_depth <= 0){
            return Color(0.0, 0.0, 0.0);
        }
        hit_info info = scene.find_hit(r, 0.001, 100);

        if (info.hit){
            Ray reflected_ray = info.material->scatter(r, info);
            // Vec3 reflection_direction = info.normal + random_reflection_direction(info.normal);
            // Ray reflected_ray(info.hit_point, reflection_direction);
            
            // Color albedo(0.7, 0.2, 0.5);
            // return  albedo * cast_sample_ray(reflected_ray, ray_depth - 1);
            return info.material->get_albedo() * cast_sample_ray(reflected_ray, ray_depth - 1);
        }

        double a = 0.5 * (unit_vect(r.direction()).y() + 1.0);
        return (1 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }
};

#endif