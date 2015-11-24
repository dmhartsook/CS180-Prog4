#include "Light.h"

Light::Light(const Vector *location, const RGB *color) {
    this->location = new Vector(*location);
    this->color = new RGB(*color);
}

Light::~Light() {
    delete this->location;
    delete this->color;
}

const Vector *Light::getLocation() const {
    return this->location;
}


const RGB *Light::getColor() const {
    return this->color;
}
