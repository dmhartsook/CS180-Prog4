#include <fstream>
#include <iostream>
#include "Ppm.h"


Ppm::Ppm(const char *filename) {
    readInImage(filename);
}

void Ppm::writePpm(const ImagePlane *imagePlane, const char *filename) {
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


void Ppm::readInImage(const char *filename) {
    std::ifstream imageFile;
    imageFile.open(filename, std::ios::binary);

    std::string width_s;
    std::string height_s;

    // TODO: Add error checking instead of just ignoring
    imageFile.ignore(100, '\n'); // ignore first line
    imageFile >> width_s;
    imageFile >> height_s;
    imageFile.get(); // skip trailing white space
    imageFile.ignore(100, '\n'); // skip 255

    int width = std::atoi(width_s.c_str());
    int height = std::atoi(height_s.c_str());

    unsigned char redChar, greenChar, blueChar;
    int r, g, b;

    this->image = new RGB **[width];
    for (int i = 0; i < width; i++) {
        this->image[i] = new RGB*[height];
        for (int j = 0; j < height; j++) {
            imageFile >> redChar;
            imageFile >> greenChar;
            imageFile >> blueChar;

            r = redChar; g = greenChar; b = blueChar;

            std::cout << "r = " << r << ", g = " << g << ", b = " << b << std::endl;
            this->image[i][j] = new RGB(0, 0, 0);
        }
    }

    imageFile.close();

    this->width = width;
    this->height = height;
}
