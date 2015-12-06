#include <assert.h>
#include <iostream>
#include "Object.h"

Object::Object(const Vector *centerVals, const RGB *color, double reflectivity, const Texture *texture) {
    assert(centerVals != NULL);
    if (color == NULL) {
        // TODO: REMOVE THIS
        color = new RGB(1,1,1);
        assert(texture != NULL);
    }

    Vector* center = new Vector(centerVals->toArray());
    this->center = center;
    this->color = new RGB(*color);

    assert(reflectivity >= 0.0 && reflectivity <= 1);
    this->reflectivity = reflectivity;

    if (texture == NULL) {
        this->texture = NULL;
    } else {
        this->texture = new Texture(*texture);
    }
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
