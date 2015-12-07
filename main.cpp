#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "ImagePlane.h"
#include "InputFile.h"
#include "Ray.h"

static const RGB BACKGROUND_COLOR(0, 0, 0);

int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);

    InputFile* inputFile;
    char* filename;
    if (argc > 1) {
        inputFile = new InputFile(argv[1]);
        filename = strtok(argv[1], ".");
        strcat(filename, ".ppm");
    } else {
        std::cerr << "Please specify an input file to read the scene data from." << std::endl;
        return 0;
    }

    Scene scene;
    scene.objects = inputFile->getObjects();
    scene.lights = inputFile->getLights();

    const int imagePlaneSize = inputFile->getCameraResolution();
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            RGB* actualColor = pixelRay->castRay(scene, 0);
            if (actualColor == NULL) {
                actualColor = new RGB(BACKGROUND_COLOR);
            }
            imagePlane->setPixelColor(i, j, actualColor);

            delete actualColor;
            delete pixelRay;
            delete[] pixel;
        }
    }

    Ppm::writePpm(imagePlane, filename);

    delete imagePlane;
    delete inputFile;

    return 0;
}


