#include "scene.h"

bool Scene::intersect(const Ray& ray, Intersection& intersection) const {
    std::vector<Intersection> intersections_;
    // find all intersections
    for (size_t i=0; i<sceneObjects_.size(); i++) {
        Intersection curIntersection;
        bool intersected = sceneObjects_[i]->intersect(ray, curIntersection);
        if (intersected)
            intersections_.push_back(curIntersection);
    }
    // determine closest intersection
    if (intersections_.size() > 0) {
        intersection = intersections_[0];
        for (size_t i=1; i<intersections_.size(); i++)
            if (intersections_[i].distance < intersection.distance)
                intersection = intersections_[i];
        return true;
    } else
        return false;
}


void Scene::addSceneObject(SceneObject* sceneObject) {
    sceneObjects_.push_back(sceneObject);
}

int Scene::getNumSceneObjects() const {
    return sceneObjects_.size();
}

SceneObject* Scene::getSceneObject(int sceneObjectID) const {
    return sceneObjects_[sceneObjectID];
}


void Scene::addLightSource(Vec3 lightSource) {
    lightSources_.push_back(lightSource);
}

int Scene::getNumLightSources() const {
    return lightSources_.size();
}

Vec3 Scene::getLightSource(int lightSourceID) const {
    return lightSources_[lightSourceID];
}