#include "sceneobject.h"

Sphere::Sphere(Vec3 center, double radius, Vec3 color) {
    center_ = center;
    radius_ = radius;
    color_ = color;
}

bool Sphere::intersect(const Ray& ray, Intersection& intersection) const {
    Vec3 dst = center_ - ray.origin;
    double B = dst.dot(ray.direction);
    double C = B*B - dst.dot(dst) + (radius_*radius_);
    if (C < 0)
        return false;
    double D = sqrt(C);
    double E = B+D;
    if (E < 0)
        return false;
    double F = B - D;
    double dist = (F > 0) ? F : E;
    dist -= 0.001f;
    intersection.pos = ray.origin + (ray.direction * dist);
    intersection.colorDiffuse = color_;
    intersection.colorAmbient = color_*0.5;
    intersection.colorSpecular = Vec3(1.0,1.0,1.0);
    intersection.distance = (ray.origin-intersection.pos).length();
    intersection.normal = (intersection.pos-center_).normalize();
    return true;
}


Plane::Plane(Vec3 normal, double delta, Vec3 color) {
    normal_ = normal;
    delta_ = delta;
    color_ = color;
}

bool Plane::intersect(const Ray& ray, Intersection& intersection) const {
    double vd = ray.direction.dot(normal_);
    if (vd == 0)
        return false;
    else {
        double v0 = -(ray.origin.dot(normal_) + delta_);
        double t = v0 / vd;
        if (t >= 0.0) {
            intersection.pos = ray.origin + (ray.direction * t);
            intersection.colorDiffuse = color_;
            intersection.colorAmbient = color_*0.5;
            intersection.colorSpecular = Vec3(1.0,1.0,1.0);
            intersection.distance = (ray.origin-intersection.pos).length();
            if (vd > 0.0) intersection.normal = Vec3(-normal_.x, -normal_.y, -normal_.z);
            else intersection.normal = normal_;
            return true;
        } else
            return false;
    }    
}
