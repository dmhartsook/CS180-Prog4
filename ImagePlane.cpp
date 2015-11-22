#include <iostream>
#include "ImagePlane.h"

const double ImagePlane::xOffset = -0.5;
const double ImagePlane::yOffset = -0.5;

ImagePlane::ImagePlane(int px, int py) {
    this->width = px;
    this->height = py;

    this->imagePlane = new RGB **[this->width];
    for (int i = 0; i < this->width; i++) {
        this->imagePlane[i] = new RGB*[this->height];
        for (int j = 0; j < this->height; j++) {
            this->imagePlane[i][j] = new RGB(0, 0, 0);
        }
    }
}

ImagePlane::~ImagePlane() {
    for (int i = 0; i < this->width; i++) {
        delete[] this->imagePlane[i];
    }
    delete[] this->imagePlane;
}

void ImagePlane::print() const {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            RGB* rgb = this->imagePlane[i][j];
            std::cout << "(" << rgb->getRed() << ", " << rgb->getGreen() << ", " << rgb->getBlue() << ")  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double* ImagePlane::getPixelCoords(int i, int j) const {
    double* pixel = new double[3];
    pixel[0] = ((double) i / (double) this->width) + xOffset;
    pixel[1] = ((double) j / (double) this->height) + yOffset;
    pixel[2] = this->zValue;
    return pixel;
}

void ImagePlane::setPixelColor(int j, int i, const RGB *newColor) {
    RGB* color = this->imagePlane[i][j];
    color->setColors(newColor->getRed(), newColor->getGreen(), newColor->getBlue());
}

int ImagePlane::getWidth() const {
    return this->width;
}

int ImagePlane::getHeight() const {
    return this->height;
}

const RGB *ImagePlane::getPixelColor(int i, int j) const {
    return this->imagePlane[i][j];
}
