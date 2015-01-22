#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "mymath.h"

class SceneObject {
public:
    virtual bool intersect(const Ray& ray, Intersection& intersection) const = 0;
};


class Sphere : public SceneObject {
public:
    Sphere(Vec3 center, double radius, Vec3 color);
    bool intersect(const Ray& ray, Intersection& intersection) const;

private:
    Vec3 center_;
    double radius_;
    Vec3 color_;
};


class Plane : public SceneObject {
public:
    Plane(Vec3 normal, double delta, Vec3 color);
    bool intersect(const Ray& ray, Intersection& intersection) const;

private:
    Vec3 normal_;
    double delta_;
    Vec3 color_;
};

#endif // SCENEOBJECT_H