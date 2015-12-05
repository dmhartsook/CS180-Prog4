#include <assert.h>
#include <iostream>
#include "Object.h"

Object::Object(const Vector *centerVals, const RGB *color, double reflectivity, Texture* texture) {
    assert(centerVals != NULL);
    if (color == NULL) {
        // TODO: REMOVE THIS
        color = new RGB(0,0,0);
        assert(texture != NULL);
    }

    Vector* center = new Vector(centerVals->toArray());
    this->center = center;
    this->color = new RGB(*color);

    assert(reflectivity >= 0.0 && reflectivity <= 1);
    this->reflectivity = reflectivity;

    this->texture = texture;
}

Object::~Object() {
    delete this->center;
}

const RGB* Object::getColor() const {
    return this->color;
}

const Vector* Object::getCenter() const {
    return this->center;
}

double Object::getReflectivity() const {
	return this->reflectivity;
}

const Texture *Object::getTexture() const {
    return this->texture;
}
