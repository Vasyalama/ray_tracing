#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray{
    public:
    Vec3 st;
    Vec3 dir;
    Ray(){};

    Ray(Vec3 s, Vec3 d) : st(s), dir(d) {};

    Vec3 start() {return st;};
    Vec3 direction() {return dir;};

    Vec3 at(double t){
        return st + dir * t;
    }


};

#endif