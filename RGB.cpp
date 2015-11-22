#include <assert.h>
#include <iostream>
#include "RGB.h"

RGB::RGB(double r, double g, double b) {
    this->setColors(r, g, b);
}

RGB::RGB(const RGB &other) {
    this->red = other.getRed();
    this->green = other.getGreen();
    this->blue = other.getBlue();
}

double RGB::getRed() const {
    return this->red;
}

double RGB::getGreen() const {
    return this->green;
}

double RGB::getBlue() const {
    return this->blue;
}

void RGB::setColors(double r, double g, double b) {
    assert(r >= 0 && r <= 1);
    assert(g >= 0 && g <= 1);
    assert(b >= 0 && b <= 1);

    this->red = r;
    this->green = g;
    this->blue = b;
}

int *RGB::convertTo255Values() const {
    int* color = new int[3];
    color[0] = (int) (this->red * 255);
    color[1] = (int) (this->green * 255);
    color[2] = (int) (this->blue * 255);
    return color;
}

void RGB::print() const {
    std::cout << "(" << this->red << ", " << this->green << ", " << this->blue << ")";
}
