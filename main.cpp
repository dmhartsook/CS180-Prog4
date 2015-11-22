#include <iostream>
#include <vector>
#include "Ray.h"
#include "ImagePlane.h"
#include "Sphere.h"


int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);
    const int imagePlaneSize = 10;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    ImagePlane* wtf = NULL;

    RGB color;
    color.red = 1; color.green = 0; color.blue = .9;
    Vector center = Vector (0, 0, -10);
    Sphere* sphere = new Sphere(center, color, .5, 5);

    std::vector<Object*> objects;
    objects.push_back(sphere);

    for (int i = 0; i <= imagePlaneSize; i++) {
        for (int j = 0; j <= imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            Vector* intersectionPoint = sphere->intersect(pixelRay);
            if (intersectionPoint != nullptr) {
                std::cout << "intersection " << std::endl;
                intersectionPoint->print();
            } else {
                std::cout << "miss" << std::endl;
            }

            delete pixelRay;
            delete[] pixel;
        }
    }

    delete imagePlane;

    return 0;
}