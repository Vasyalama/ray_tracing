#ifndef COLOR_H
#define COLOR_H
#include <iostream>


inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);

    return 0;
}

class Color{
public:
    double c[3];
    Color(): c{0.0, 0.0, 0.0} {};
    Color(double r, double g, double b): c{r, g, b} {};

    double r() const { return c[0]; };
    double g() const { return c[1]; };
    double b() const { return c[2]; };

    double operator[](int index) const { return c[index]; };
    double& operator[](int index) {return c[index]; };  

    void write_to_ppm(std::ostream& out){

        int r = int(255.999 * linear_to_gamma(c[0]));
        int g = int(255.999 * linear_to_gamma(c[1]));
        int b = int(255.999 * linear_to_gamma(c[2]));
        out << r << " " << g << " " << b << std::endl;
    }

    Color& operator+=(const Color& other){
        c[0] += other[0];
        c[1] += other[1];
        c[2] += other[2];
        return *this;
    }

    Color& operator*=(double a){
        c[0] *= a;
        c[1] *= a;
        c[2] *= a;
        return *this;
    }

    Color& operator/=(double a){
        *this *= (1/a);
        return *this;
    } 

};



inline std::ostream& operator<<(std::ostream& out, const Color& c){
    out << c.r() << " " << c.g() << c.b();
    return out;
}

inline Color operator+(const Color& c1, const Color& c2){
    return Color(c1[0] + c2[0], c1[1] + c2[1], c1[2] + c2[2]);
}

inline Color operator-(const Color& c1, const Color& c2){
    return Color(c1[0] - c2[0], c1[1] - c2[1], c1[2] - c2[2]);
}

inline Color operator*(const Color& c1, const Color& c2){
    return Color(c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]);
}
inline Color operator*(const Color& c, double a){
    return Color(c[0] * a, c[1] * a, c[2] * a);
}

inline Color operator*(double a, const Color& c){
    return c * a;
}

#endif