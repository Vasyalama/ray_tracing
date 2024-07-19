#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "utilss.h"

class Vec3{
public:
    double p[3];

    Vec3(): p{0,0,0} {};
    Vec3(double x, double y, double z): p{x, y, z} {};

    double x() { return p[0]; };
    double y() { return p[1]; };
    double z() { return p[2]; };

    double length_squared() const {
        return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double operator[](int index) const { return p[index]; };
    double& operator[](int index) {return p[index]; };

    Vec3 operator-() { return Vec3(-p[0], -p[1], -p[2]); };
    
    Vec3& operator+=(const Vec3& other){
        p[0] += other[0];
        p[1] += other[1];
        p[2] += other[2];
        return *this;
    }

    Vec3& operator*=(double a){
        p[0] *= a;
        p[1] *= a;
        p[2] *= a;
        return *this;
    }

    Vec3& operator/=(double a){
        *this *= (1/a);
        return *this;
    }  

    static Vec3 random_vector(double min, double max){
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool close_to_zero(){
        if (std::fabs(p[0] - 0.0) < 0.001 || 
            std::fabs(p[1] - 0.0) < 0.001 ||
            std::fabs(p[2] - 0.0) < 0.001){
                return true;
            }
        
        return false;
    }



    
};

inline std::ostream& operator<<(std::ostream& out, const Vec3& v){
    out << v[0] << " " << v[1] << " " << v[2];
    return out;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v){
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v){
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3& u, double a){
    return Vec3(u[0] * a, u[1] * a, u[2] * a);
}

inline Vec3 operator*(double a, const Vec3& u){
    return u * a;
}

inline Vec3 operator/(const Vec3& u, double a){
    return u * (1/a);
}

inline double dot(const Vec3& u, const Vec3& v){
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline double cross(){
    std::cout << "cross() not implemented\n";
    exit(-1);
}

inline Vec3 unit_vect(const Vec3& v){
    return v / v.length();
}

inline Vec3 random_unit_vector(){
    Vec3 random_vec = Vec3::random_vector(-1.0, 1.0);
    while(random_vec.length_squared() > 1.0){
        random_vec = Vec3::random_vector(-1.0, 1.0);
    }
    return unit_vect(random_vec);
}


Vec3 reflect(Vec3 v, Vec3& normal){
    return v - 2 * dot(v, normal) * normal;
}


#endif