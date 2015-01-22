#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"
#include <vector>

class Scene {
public:
    bool intersect(const Ray& ray, Intersection& intersection) const;

    void addSceneObject(SceneObject* sceneObject);
    int getNumSceneObjects() const;
    SceneObject* getSceneObject(int sceneObjectID) const;

    void addLightSource(Vec3 lightSource);
    int getNumLightSources() const;
    Vec3 getLightSource(int lightSourceID) const;

private:
    std::vector<SceneObject*> sceneObjects_;
    std::vector<Vec3> lightSources_;
};

#endif // SCENE_H