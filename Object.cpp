#include <assert.h>
#include "Object.h"

Object::Object(Vector centerVals, RGB color, double reflectivity) {
    Vector* center = new Vector(centerVals.get(0), centerVals.get(1), centerVals.get(2));
    this->center = center;
    this->color = color;

    assert(reflectivity >= 0.0 && reflectivity <= 1);
    this->reflectivity = reflectivity;
}

Object::~Object() {
    delete this->center;
}

RGB Object::getColor() {
    return this->color;
}

Vector Object::getCenter() {
    return *this->center;
}
