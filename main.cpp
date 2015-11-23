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

int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);
    const int imagePlaneSize = 1000;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    RGB* sphereColor = new RGB(1, 1, 1);
    Vector* sphereCenter = new Vector (0, 0, -5);
    Sphere* sphere = new Sphere(sphereCenter, sphereColor, .5, 2);
    delete sphereColor;
    delete sphereCenter;

    RGB* lightColor = new RGB(1, 1, 1);
    Vector* lightLocation = new Vector(1, 1,1);
    Light* light = new Light(lightLocation, lightColor);
    delete lightColor;
    delete lightLocation;


    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            const Vector* intersectionPoint = sphere->intersect(pixelRay);
            const RGB* materialColor;
            if (intersectionPoint != nullptr) {
                Ray* lightRay = new Ray(*intersectionPoint, *light->getLocation());
                Vector* normal = sphere->getNormal(intersectionPoint);
                double angle = normal->angleBetween(*lightRay);

                materialColor = sphere->getColor();
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

    delete sphere;
    delete light;

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
