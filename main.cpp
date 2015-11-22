#include <fstream>
#include <iostream>
#include "ImagePlane.h"
#include "Ray.h"
#include "Sphere.h"
#include <vector>

static const char *const IMAGE_FILENAME = "scene.ppm";

void writePpm(const ImagePlane *, const char *filename);

int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);
    const int imagePlaneSize = 400;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    RGB* color = new RGB(1, 1, 1);
    Vector* center = new Vector (0, -1, -5);
    Sphere* sphere = new Sphere(center, color, .5, 1);

    std::vector<Object*> objects;
    objects.push_back(sphere);

    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
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

    writePpm(imagePlane, IMAGE_FILENAME);

    delete imagePlane;

    return 0;
}


void writePpm(const ImagePlane *imagePlane, const char *filename) {
    std::ofstream image;
    image.open(filename, std::ios::binary);

    image << "P6" << "\n"
        << imagePlane->getWidth() << " " << imagePlane->getHeight() << "\n"
        << "255\n";

    for (int j = imagePlane->getHeight() - 1; j >= 0; j--) {
        for (int i = 0; i < imagePlane->getWidth(); i++)  {
            const RGB *color = imagePlane->getPixelColor(i, j);
            int* colorVals = color->convertTo255Values();

            image << (unsigned char) colorVals[0] << (unsigned char) colorVals[1] << (unsigned char) colorVals[2];

            delete[] colorVals;
        }
        image << "\n";
    }

    image.close();
}
