#include <stdlib.h>

#include "mymath.h"
#include "myimage.h"
#include "scene.h"
#include "sceneobject.h"


Scene* myScene;


Scene* createScene1() {
	Scene* result = new Scene();
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 0.0), 0.1, Vec3(1.0, 1.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.2, 0.0, 0.0), 0.1, Vec3(1.0, 0.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.4, 0.0, 0.0), 0.1, Vec3(1.0, 0.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.6, 0.0, 0.0), 0.1, Vec3(1.0, 0.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.8, 0.0, 0.0), 0.1, Vec3(1.0, 0.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(1.0, 0.0, 0.0), 0.1, Vec3(1.0, 0.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.2, 0.0), 0.1, Vec3(0.0, 1.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.4, 0.0), 0.1, Vec3(0.0, 1.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.6, 0.0), 0.1, Vec3(0.0, 1.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.8, 0.0), 0.1, Vec3(0.0, 1.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 1.0, 0.0), 0.1, Vec3(0.0, 1.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 0.2), 0.1, Vec3(0.0, 0.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 0.4), 0.1, Vec3(0.0, 0.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 0.6), 0.1, Vec3(0.0, 0.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 0.8), 0.1, Vec3(0.0, 0.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 1.0), 0.1, Vec3(0.0, 0.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.5, 0.5, 0.0), 0.2, Vec3(1.0, 1.0, 0.0)));
	result->addSceneObject(new Plane(Vec3(0.0, 1.0, 0.0), 0.1, Vec3(0.3, 0.3, 0.3)));
	result->addLightSource(Vec3(1.0, 1.0, 1.0));
	return result;
}

Scene* createScene2() {
	Scene* result = new Scene();
	result->addSceneObject(new Plane(Vec3(0.0, 1.0, 0.0), 0.0, Vec3(0.3, 0.3, 0.3)));
	result->addSceneObject(new Sphere(Vec3(0.05, 0.3, 0.0), 0.3, Vec3(0.8, 0.2, 0.2)));
	result->addSceneObject(new Sphere(Vec3(0.4, 0.1, 0.1), 0.1, Vec3(0.0, 1.0, 0.0)));
	result->addSceneObject(new Sphere(Vec3(-0.35, 0.25, -0.15), 0.25, Vec3(0.5, 0.5, 0.1)));
	result->addSceneObject(new Sphere(Vec3(-0.35, 0.15, 0.3), 0.15, Vec3(0.0, 0.0, 1.0)));
	result->addSceneObject(new Sphere(Vec3(0.15, 0.6, -1.0), 0.6, Vec3(0.2, 0.4, 0.5)));
	result->addLightSource(Vec3(1.0, 1.5, 1.0));
	return result;
}


Scene* createScene3(int recursion) {
	Scene* result = new Scene();
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 0.0), 1.0*recursion, Vec3(0.8, 0.8, 0.8)));
	result->addSceneObject(new Sphere(Vec3(1.0*recursion, 0.0, 0.0), 0.5*recursion, Vec3(0.8, 0.8, 0.8)));
	result->addSceneObject(new Sphere(Vec3(0.0, 1.0*recursion, 0.0), 0.5*recursion, Vec3(0.8, 0.8, 0.8)));
	result->addSceneObject(new Sphere(Vec3(0.0, 0.0, 1.0*recursion), 0.5*recursion, Vec3(0.8, 0.8, 0.8)));
	return result;
}


Vec3 shadingLambert(const Intersection& intersection) {
    Vec3 resultColor = Vec3();
    for (int i=0; i<myScene->getNumLightSources(); i++) {
        Vec3 lightVector = (myScene->getLightSource(i)-intersection.pos).normalize();
        double lambert = lightVector.dot(intersection.normal);
        if (lambert > 0.0)
            resultColor = resultColor + intersection.colorDiffuse*lambert;
    }
    return resultColor;
}

Vec3 shadingBlinnPhong(const Intersection& intersection, const Ray& viewRay) {
    Vec3 resultColor = Vec3();
    for (int i=0; i<myScene->getNumLightSources(); i++) {
        Vec3 viewVector = (viewRay.origin-intersection.pos).normalize();
        Vec3 lightVector = (myScene->getLightSource(i)-intersection.pos).normalize();
        Vec3 halfWayVector = (viewVector + lightVector).normalize();
        double specular = intersection.normal.dot(halfWayVector);
        if (specular > 0.0)
            resultColor = resultColor + intersection.colorSpecular*pow(specular, 120.0);
    }
    return resultColor;
}

Vec3 shadingAmbient(const Intersection& intersection) {
    Vec3 resultColor = Vec3();
    resultColor = intersection.colorAmbient;
    return resultColor;
}

bool isShadowed(const Intersection& intersection) {
    bool result = true;
    for (int i=0; i<myScene->getNumLightSources(); i++) {
        Vec3 lightVector = (myScene->getLightSource(i)-intersection.pos).normalize();
        lightVector = lightVector.normalize();
        Ray lightRay = Ray(intersection.pos+lightVector*0.001, lightVector);
        Intersection lightRayIntersection;
        if (!myScene->intersect(lightRay, lightRayIntersection))
            result = false;
    }
    return result;
}

Vec3 rayColor(const Ray& ray, int recursion) {
	Vec3 resultColor;
	if (recursion <= 0) return resultColor;
	Intersection intersection;
	if (myScene->intersect(ray, intersection)) {
		resultColor = resultColor + shadingAmbient(intersection);
		if (!isShadowed(intersection)) {
			resultColor = resultColor + shadingLambert(intersection);
			resultColor = resultColor + shadingBlinnPhong(intersection, ray);
		}
		if (resultColor.length() > 0.0) {
			Vec3 reflectionVector = ray.direction - intersection.normal * 2 * (ray.direction.dot(intersection.normal));
			Ray reflectionRay = Ray(intersection.pos + reflectionVector*0.001, reflectionVector);
			resultColor = resultColor + intersection.colorSpecular.mult(rayColor(reflectionRay, recursion-1));
		}
	}
	return resultColor;
}

int main(int argc, char* argv[]) {
    // initialize variables
    int nx = argc>1 ? atoi(argv[1]) : 512; // image width
    int ny = argc>2 ? atoi(argv[2]) : 512; // image height

    // define camera vectors
    Vec3 e = Vec3(0.0, 4.0, -1.0); // x // z // y
    Vec3 u = Vec3(1.0, 0.0, 0.0);
    Vec3 v = Vec3(0.0, 1.0, -1.0);
    Vec3 w = Vec3(0.0, 1.0, 0.0);

    // define image plane borders
    double l = -0.05;
    double r =  0.05;
    double b = -0.05;
    double t =  0.05;
    double n =  0.1;

    // scene setup
    //myScene = createScene1();
    myScene = createScene2();

    // generate result buffer
    Vec3* image = new Vec3[nx*ny]; 

    for (int x=0; x<nx; x++) {
        for (int y=0; y<ny; y++) {
            int imageIndex = (ny-y-1)*nx + x;

            // compute camera ray direction
            double su = l+(r-l)*(double(x)+0.5)/double(nx);
            double sv = b+(t-b)*(double(y)+0.5)/double(ny);
            double sw = -n;
            Vec3 cameraRayDirection = (u*su + v*sv + w*sw).normalize();
            Ray cameraRay = Ray(e, cameraRayDirection);

			Vec3 resultColor = rayColor(cameraRay, 3);
            image[imageIndex] = resultColor;
        }
    }
    saveAsPPM(nx, ny, image);

	return 0;
}