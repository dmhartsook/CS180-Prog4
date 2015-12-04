#include "Light.h"
#include <iostream>

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

void Light::print() const {
	std::cout << "Light: " << std::endl;
	std::cout << "    Location: ";
	this->location->print();
	std::cout << "    Color:";
	this->color->print();
	std::cout << std::endl;
}
