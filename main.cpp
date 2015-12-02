#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "ImagePlane.h"
#include "InputFile.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include <utility>
#include "Light.h"
#include "InputFile.h"
#include "Scene.h"
#include <vector>

static const char *const IMAGE_FILENAME = "scene.ppm";
static const double EPSILON = .0001;
static const RGB BACKGROUND_COLOR(0, 0, 0);

void writePpm(const ImagePlane *, const char *filename);
std::pair<const Vector *, const Object *> findIntersection(const Ray *ray, std::vector<const Object *> &objects);
RGB *castRay(const Ray *ray, Scene scene, int depth);
RGB *determineColor(const Object *object, const Vector *intersectionPoint, Scene scene);

const Object * intersectObject(const Ray *ray, std::vector<const Object *>& objects);


int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);

    InputFile* inputFile;
    if (argc > 1) {
        inputFile = new InputFile(argv[1]);
    } else {
        inputFile = new InputFile("two_spheres.txt");
    }

    Scene scene;
    scene.objects = inputFile->getObjects();
    scene.lights = inputFile->getLights();

    const int imagePlaneSize = inputFile->getCameraResolution();
//    const int imagePlaneSize = 200;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

//    for (int i = 0; i < objects.size(); i++){
//        objects[i]->print();
//    }

//    RGB* sphereColor = new RGB(1, 1, 1);
//    Vector* sphereCenter = new Vector (0, 0, -5);
//    const Sphere* sphere = new Sphere(sphereCenter, sphereColor, 1, 1);
//    delete sphereColor;
//    delete sphereCenter;
//
//    RGB* lightColor = new RGB(1, 1, 1);
//    Vector* lightLocation = new Vector(1, 1,1);
//    const Light* light = new Light(lightLocation, lightColor);
//    delete lightColor;
//    delete lightLocation;

//    objects.push_back(sphere);
//    lights.push_back(light);

//    Vector* v1 = new Vector(1, 1, 0);
//    Vector* v2 = new Vector(3, 0, 0);
//    std::cout << v1->distance(v2) << std::endl;
//
//    return  0;

//    RGB* r1 = new RGB(.2, .4, .7);
//    RGB* r2 = new RGB(.1, .6, .5);
//    r1->add(r2);
//    r1->print();
//    std::cout << std::endl;
//
//    return 0;

//    Vector start = Vector(3, 0, 0);
//    Vector end = Vector(0,0, -4);
//    Ray* ray = new Ray(start, end);
//    std::cout << "original ray: ";
//    ray->print();
//    Vector point = Vector(0, 0, -4);
//    std::cout << "reflected at point ";
//    point.print();
//    Vector* normal = sphere->getNormal(&point);
//    Vector* reflectedDir = ray->createReflectedVector(normal);
//    std::cout << "reflectedDir: ";
//    reflectedDir->print();
//
//    reflectedDir->add(&point);
//
//    std::cout << "reflect: ";
//    Ray* reflect = new Ray(point, *reflectedDir);
//    reflect->print();
//
//    return 0;


    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

//            RGB* actualColor = castRay(pixelRay, scene, 0);
            RGB* actualColor = pixelRay->castRay(scene);
            if (actualColor == NULL) {
                actualColor = new RGB(BACKGROUND_COLOR);
            }
            imagePlane->setPixelColor(i, j, actualColor);

            delete actualColor;
            delete pixelRay;
            delete[] pixel;
        }
    }

    writePpm(imagePlane, IMAGE_FILENAME);

    delete imagePlane;
    delete inputFile;

    return 0;
}

/*
 * Casts a ray into the scene and determines the color at its origin.
 * The depth is the number of times this function
 */
RGB *castRay(const Ray *ray, Scene scene, int depth) {
    std::pair<const Vector*, const Object*> intersection = findIntersection(ray, scene.objects);
    const Vector* intersectionPoint = intersection.first;
    const Object* intersectedObject = intersection.second;
    if (intersectionPoint != NULL) {
        return determineColor(intersectedObject, intersectionPoint, scene);
    } else {
        return new RGB(BACKGROUND_COLOR);
    }
}

/*
 * Determines the color of the object at the intersectionPoint from the lights.
 * Sum(lightColor*materialColor*cos(angleFromNormalToLight).
 * Returns a new RGB object that must be destroyed.
 */
RGB *determineColor(const Object *object, const Vector *intersectionPoint, Scene scene) {
    RGB* actualColor = new RGB(0, 0, 0);
    const RGB* materialColor = object->getColor();
    Vector *normal = object->getNormal(intersectionPoint);

    for (int i = 0; i < scene.lights.size(); i++) {
        Ray *lightRay = new Ray(*intersectionPoint, *(scene.lights[i]->getLocation()));
        lightRay->move(EPSILON); // Move out to prevent ray from incorrectly colliding with the object.

        const Object *intersectedObject = intersectObject(lightRay, scene.objects);

        if (intersectedObject == NULL) { // Not in shadow
            double angle = normal->angleBetween(*lightRay);

            RGB *colorFromLight = new RGB(*materialColor);
            // if cos(angle) < 0 then in shadow so multiply by 0
            colorFromLight->multiply(std::max(0.0, cos(angle)));
            colorFromLight->multiply(scene.lights[i]->getColor());

            actualColor->add(colorFromLight);

            delete colorFromLight;
        } else if (intersectedObject->getReflectivity() > 0) { // reflection

        }
    }

    return actualColor;
}

/*
 * Returns the intersected object if the ray intersects any object in the vector of objects.
 * Returns NULL if the ray does not intersect any objects.
 */
const Object * intersectObject(const Ray *ray, std::vector<const Object *>& objects) {
    for (int i = 0; i < objects.size(); i++) {
        const Vector* intersectionPoint = objects[i]->intersect(ray);
        if (intersectionPoint != NULL) {
            return objects[i];
        }
    }

    return NULL;
}

/*
 * Finds the interesection between the ray and the closest object.
 * Returns the intersection point, which is a new vector and must be deleted.
 * Also returns the object that was intersected.
 */
std::pair<const Vector *, const Object *> findIntersection(const Ray *ray, std::vector<const Object *> &objects) {
    const Vector* closestPoint = NULL;
    const Object* closestObject = NULL;
    double distanceClosest = INFINITY;
    for (int i = 0; i < objects.size(); i++) {
        const Vector* intersectionPoint = objects[i]->intersect(ray);
        if (intersectionPoint != NULL) {
            double intersectDistance = ray->getStart()->distance(intersectionPoint);
            if (intersectDistance < distanceClosest) {
                closestObject = objects[i];
                closestPoint = intersectionPoint;
                distanceClosest = intersectDistance;
            }
        }

    }
    return std::make_pair(closestPoint, closestObject);
}


void writePpm(const ImagePlane *imagePlane, const char *filename) {
    std::ofstream image;
    image.open(filename, std::ios::binary);

    image << "P3" << "\n"
        << imagePlane->getWidth() << " " << imagePlane->getHeight() << "\n"
        << "255\n";

    for (int j = imagePlane->getHeight() - 1; j >= 0; j--) {
        for (int i = 0; i < imagePlane->getWidth(); i++)  {
            const RGB *color = imagePlane->getPixelColor(i, j);
            int* colorVals = color->convertTo255Values();

            image << colorVals[0] << " " <<  colorVals[1] << " " << colorVals[2] << "  ";

            delete[] colorVals;
        }
        image << "\n";
    }

    image.close();
}
