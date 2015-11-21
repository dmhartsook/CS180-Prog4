#include <iostream>
#include <vector>
#include "Ray.h"
#include "ImagePlane.h"
#include "Sphere.h"


int main(int argc, char** argv) {
    Vector* eye = new Vector(0, 0, 0);
    const int imagePlaneSize = 10;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    RGB color;
    color.red = 1; color.green = 0; color.blue = .9;
    Vector* center = new Vector (0, 0, -10);
    Sphere* sphere = new Sphere(*center, color, .5, 5);
    delete(center);

    Vector* end = new Vector(0,0,-2);
    Ray* ray = new Ray(*eye, *end);
    delete end;
    ray->print();

    if (sphere->intersect(*ray)) {
        std::cout << "intersection " << std::endl;
    } else {
        std::cout << "miss" << std::endl;
    }


    std::vector<Object*> objects;
    objects.push_back(sphere);

    for (int i = 0; i <= imagePlaneSize; i++) {
        for (int j = 0; j <= imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector* pixelVector = new Vector(pixel);
            Ray* pixelRay = new Ray(*eye, *pixelVector);
            delete pixelVector;


            delete pixelRay;
            delete[] pixel;
        }
    }

    delete imagePlane;
    delete eye;

    return 0;
}