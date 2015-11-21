#include <iostream>
#include <vector>
#include "Ray.h"
#include "ImagePlane.h"
#include "Sphere.h"


int main(int argc, char** argv) {
    double eye[3] = {0.0, 0.0, 0.0};
    const int imagePlaneSize = 10;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    RGB color;
    color.red = 1; color.green = 0; color.blue = .9;
    Vector* center = new Vector (0, 0, -10);
    Sphere* sphere = new Sphere(*center, color, .5, 5);
    delete(center);

    sphere->getCenter().print();

    double end[3] = {0,0,-1};
    Ray* ray = new Ray(eye, end);
    if (sphere->intersect(ray)) {
        std::cout << "intersection " << std::endl;
    } else {
        std::cout << "miss" << std::endl;
    }


    std::vector<Object*> objects;
    objects.push_back(sphere);

    for (int i = 0; i <= imagePlaneSize; i++) {
        for (int j = 0; j <= imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Ray* pixelRay = new Ray(eye, pixel);


            delete pixelRay;
            delete[] pixel;
        }
    }

    delete imagePlane;


    return 0;
}