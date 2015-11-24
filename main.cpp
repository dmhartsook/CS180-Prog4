#include <fstream>
#include <iostream>
#include "ImagePlane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include <vector>
#include <cmath>

static const char *const IMAGE_FILENAME = "scene.ppm";

void writePpm(const ImagePlane *, const char *filename);

std::pair<const Vector *, const Object *> findIntersection(const Ray *ray, std::vector<const Object *> objects);

int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);
    const int imagePlaneSize = 500;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    RGB* sphereColor = new RGB(1, 1, 1);
    Vector* sphereCenter = new Vector (0, 0, -5);
    const Sphere* sphere = new Sphere(sphereCenter, sphereColor, .5, 2);
    delete sphereColor;
    delete sphereCenter;

    RGB* lightColor = new RGB(1, 1, 1);
    Vector* lightLocation = new Vector(1, 1,1);
    const Light* light = new Light(lightLocation, lightColor);
    delete lightColor;
    delete lightLocation;

    std::vector<const Object*> objects;
    std::vector<const Light*> lights;
    objects.push_back(sphere);
    lights.push_back(light);

//    Vector* v1 = new Vector(1, 1, 0);
//    Vector* v2 = new Vector(3, 0, 0);
//    std::cout << v1->distance(v2) << std::endl;
//
//    return  0;


    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            std::pair<const Vector*, const Object*> intersection = findIntersection(pixelRay, objects);
            const Vector* intersectionPoint = intersection.first;
            const Object* intersectedObject = intersection.second;

            const RGB* materialColor;
            if (intersectionPoint != NULL) {
                Ray* lightRay = new Ray(*intersectionPoint, *light->getLocation());
                Vector* normal = intersectedObject->getNormal(intersectionPoint);
                double angle = normal->angleBetween(*lightRay);

                materialColor = intersectedObject->getColor();
                RGB* actualColor = new RGB(*materialColor);
                actualColor->multiply(std::abs(cos(angle)));
                actualColor->multiply(light->getColor());

                imagePlane->setPixelColor(i, j, actualColor);
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

    return 0;
}

/*
 * Finds the interesection between the ray and the closest object.
 * Returns the intersection point, which is a new vector and must be deleted.
 * Also returns the object that was intersected.
 */
std::pair<const Vector *, const Object *> findIntersection(const Ray *ray, std::vector<const Object *> objects) {
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
