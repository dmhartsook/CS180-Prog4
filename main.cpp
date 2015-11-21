#include <iostream>
#include "Ray.h"
#include "ImagePlane.h"
#include "Sphere.h"


int main(int argc, char** argv) {
    double eye[3] = {0.0, 0.0, 0.0};
    const int imagePlaneSize = 10;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    for (int i = 0; i <= imagePlaneSize; i++) {
        for (int j = 0; j <= imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Ray* pixelRay = new Ray(eye, pixel);


            delete pixelRay;
            delete[] pixel;
        }
    }

    delete imagePlane;

    RGB color;
    color.red = 1; color.green = 0; color.blue = .9;
    Sphere* s = new Sphere(eye, color, .5, 5);
    std::cout << s->getColor().red << ", " << s->getColor().green << ", " << s->getColor().blue << std::endl;
    std::cout << s->getCenter()[0] << s->getCenter()[1] << s->getCenter()[2] << std::endl;

    return 0;
}