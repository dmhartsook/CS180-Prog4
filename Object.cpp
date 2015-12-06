#include <assert.h>
#include <iostream>
#include "Object.h"

Object::Object(const Vector *centerVals, const RGB *color, double reflectivity, const Texture *texture) {
    assert(centerVals != NULL);
    if (color == NULL) {
        assert(texture != NULL);
        this->texture = new Texture(*texture);
        this->color = NULL;
    } else if (texture == NULL) {
        assert(color != NULL);
        this->color = new RGB(*color);
        this->texture = NULL;
    }

    Vector* center = new Vector(centerVals->toArray());
    this->center = center;

    assert(reflectivity >= 0.0 && reflectivity <= 1);
    this->reflectivity = reflectivity;
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
