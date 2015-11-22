#include <iostream>
#include <vector>
#include "Ray.h"
#include "ImagePlane.h"
#include "Sphere.h"
#include "RGB.h"


int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);
    const int imagePlaneSize = 10;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    RGB* color = new RGB(1, 0, .9);
    Vector* center = new Vector (0, 0, -5);
    Sphere* sphere = new Sphere(center, color, .5, 1);

    std::vector<Object*> objects;
    objects.push_back(sphere);

    for (int i = 0; i <= imagePlaneSize; i++) {
        for (int j = 0; j <= imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            Vector* intersectionPoint = sphere->intersect(pixelRay);
            const RGB* color;
            if (intersectionPoint != nullptr) {
                color = sphere->getColor();
                imagePlane->setPixelColor(i, j, color);
            }

            delete intersectionPoint;
            delete pixelRay;
            delete[] pixel;
        }
    }

    delete imagePlane;

    return 0;
}