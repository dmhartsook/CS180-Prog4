#include <fstream>
#include <iostream>
#include "ImagePlane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "InputFile.h"
#include <vector>
#include <cmath>

static const char *const IMAGE_FILENAME = "scene.ppm";

void writePpm(const ImagePlane *, const char *filename);
std::pair<const Vector *, const Object *> findIntersection(const Ray *ray, std::vector<const Object *> &objects);
RGB *determineColor(const Object *object, const Vector *intersectionPoint, std::vector<const Light *> lights,
                    std::vector<const Object *> objects);

const Object * intersectObject(const Ray *ray, std::vector<const Object *>& objects);

int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);

    InputFile* inputFile = new InputFile("two_spheres.txt");
    std::vector<const Object*> objects = inputFile->getObjects();
    std::vector<const Light*> lights = inputFile->getLights();

    const int imagePlaneSize = inputFile->getCameraResolution();
//    const int imagePlaneSize = 200;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

//    for (int i = 0; i < objects.size(); i++){
//        objects[i]->print();
//    }

//    RGB* sphereColor = new RGB(1, 1, 1);
//    Vector* sphereCenter = new Vector (0, 0, -5);
//    const Sphere* sphere = new Sphere(sphereCenter, sphereColor, 1, 2);
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


    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            std::pair<const Vector*, const Object*> intersection = findIntersection(pixelRay, objects);
            const Vector* intersectionPoint = intersection.first;
            const Object* intersectedObject = intersection.second;

            if (intersectionPoint != NULL) {
                RGB* actualColor = determineColor(intersectedObject, intersectionPoint, lights, objects);
                imagePlane->setPixelColor(i, j, actualColor);
                delete actualColor;
            }

            delete intersectionPoint;
            delete pixelRay;
            delete[] pixel;
        }
    }

    writePpm(imagePlane, IMAGE_FILENAME);

    objects.clear();
    lights.clear();

    delete imagePlane;
    delete inputFile;

    return 0;
}

/*
 * Determines the color of the object at the intersectionPoint from the lights.
 * Sum(lightColor*materialColor*cos(angleFromNormalToLight).
 * Returns a new RGB object that must be destroyed.
 */
RGB *determineColor(const Object *object,
                    const Vector *intersectionPoint,
                    std::vector<const Light *> lights,
                    std::vector<const Object *> objects) {
    RGB* actualColor = new RGB(0, 0, 0);
    const RGB* materialColor = object->getColor();
    Vector *normal = object->getNormal(intersectionPoint);

//    std::cout << "determining color of ";
//    object->print();
//    std::cout << " at ";
//    intersectionPoint->print();

    for (int i = 0; i < lights.size(); i++) {
        Ray *lightRay = new Ray(*intersectionPoint, *(lights[i]->getLocation()));

        const Object *intersectedObject = intersectObject(lightRay, objects);

        if (intersectedObject == NULL || intersectedObject == object) { // Not in shadow
            double angle = normal->angleBetween(*lightRay);

            RGB *colorFromLight = new RGB(*materialColor);
            colorFromLight->multiply(std::abs(cos(angle)));
            colorFromLight->multiply(lights[i]->getColor());

            actualColor->add(colorFromLight);

            delete colorFromLight;
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
//            std::cout << "Ray: ";
//            ray->print();
//            std::cout << "intersected ";
//            objects[i]->print();
//            std::cout << " at: ";
//            intersectionPoint->print();
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
