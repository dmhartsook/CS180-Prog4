#include "Object.h"

Object::Object(double *center, RGB color) {
    this->center[0] = center[0];
    this->center[1] = center[1];
    this->center[2] = center[2];
    this->color = color;
}

RGB Object::getColor() {
    return this->color;
}
