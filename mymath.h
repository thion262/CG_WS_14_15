#ifndef MYMATH_H
#define MYMATH_H

#include <math.h>

struct Vec3 {
    double x, y, z;
    Vec3(double x_=0.0, double y_=0.0, double z_=0.0) {
        x = x_;
        y = y_;
        z = z_;
    }

    Vec3 operator+(const Vec3& b) const { return Vec3(x+b.x, y+b.y, z+b.z); }
    Vec3 operator-(const Vec3& b) const { return Vec3(x-b.x, y-b.y, z-b.z); }
    Vec3 operator*(double b) const { return Vec3(x*b, y*b, z*b); }
    Vec3 operator/(double b) const { return Vec3(x/b, y/b, z/b); }

	double dot(const Vec3& b) const { return x*b.x + y*b.y + z*b.z; }
	Vec3 mult(const Vec3& b) const { return Vec3(x*b.x, y*b.y, z*b.z); }
	double length() { return sqrt(x*x + y*y + z*z); }
    Vec3& normalize() { return *this = *this*(1.0/sqrt(x*x+y*y+z*z)); }
};


struct Ray {
    Vec3 origin;
    Vec3 direction;
    Ray(Vec3 origin_, Vec3 direction_) {
        origin = origin_;
        direction = direction_;
    }
};

struct Intersection {
    Vec3 pos;
    Vec3 normal;
    double distance;
    Vec3 colorDiffuse;
    Vec3 colorSpecular;
    Vec3 colorAmbient;

    Intersection() {
        pos = Vec3(0.0, 0.0, 0.0);
        normal = Vec3(1.0, 0.0, 0.0);
        distance = 100000.0;
        colorDiffuse = Vec3(1.0, 1.0, 1.0);
    }

    Intersection(Vec3 pos_, Vec3 normal_, double distance_, Vec3 color_) {
        pos = pos_;
        normal = normal_;
        distance = distance_;
        colorDiffuse = color_;
        colorSpecular = Vec3(1.0, 1.0, 1.0);
        colorAmbient = color_*0.5;
    }
};

#endif // MYMATH_H