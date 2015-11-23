#include <assert.h>
#include "Object.h"

Object::Object(const Vector *centerVals, const RGB *color, double reflectivity) {
    Vector* center = new Vector(centerVals->toArray());
    this->center = center;
    this->color = new RGB(*color);

    assert(reflectivity >= 0.0 && reflectivity <= 1);
    this->reflectivity = reflectivity;
}

Object::~Object() {
    delete this->center;
}

const RGB* Object::getColor() {
    return this->color;
}

const Vector* Object::getCenter() {
    return this->center;
}