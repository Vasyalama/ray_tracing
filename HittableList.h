#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hitable.h"
#include <vector>
#include <memory>

class HittableList: public Hitable {
public:
    std::vector<std::shared_ptr<Hitable>> objects;
    HittableList(){};

    void push_back(std::shared_ptr<Hitable> object){
        objects.push_back(object);
    }

    hit_info find_hit(Ray& ray, double low_t, double high_t) override {
        double closest_t = high_t;
        hit_info closest_hit_info;
        for (auto object: objects){
            hit_info curr_info = object->find_hit(ray, low_t, closest_t);
            if (curr_info.hit){
                closest_hit_info = curr_info;
                closest_t = curr_info.t;
            }
        }
        return closest_hit_info;
    }
};

#endif