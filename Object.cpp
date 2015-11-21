#include <assert.h>
#include "Object.h"

Object::Object(double *center, RGB color, double reflectivity) {
    this->center[0] = center[0];
    this->center[1] = center[1];
    this->center[2] = center[2];
    this->color = color;

    assert(reflectivity >= 0.0 && reflectivity <= 1);
    this->reflectivity = reflectivity;
}

RGB Object::getColor() {
    return this->color;
}

double* Object::getCenter() {
    return this->center;
}
