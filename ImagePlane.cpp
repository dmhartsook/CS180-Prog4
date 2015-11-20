#include <iostream>
#include "ImagePlane.h"

ImagePlane::ImagePlane(int width, int height) {
    this->imagePlane = new RGB*[width];
    for (int i = 0; i < width; i++) {
        this->imagePlane[i] = new RGB[height];
    }
    this->width = width;
    this->height = height;
}

ImagePlane::~ImagePlane() {
    for (int i = 0; i < this->width; i++) {
        delete[] this->imagePlane[i];
    }
    delete[] this->imagePlane;
}

void ImagePlane::print() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            RGB &rgb = this->imagePlane[i][j];
            std::cout << "(" << rgb.red << ", " << rgb.green << ", " << rgb.blue << ")  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
