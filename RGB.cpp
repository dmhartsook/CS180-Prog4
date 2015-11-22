#include "RGB.h"

RGB::RGB(double r, double g, double b) {
    this->red = r;
    this->green = g;
    this->blue = b;
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
