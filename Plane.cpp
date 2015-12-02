#include <iostream>
#include "Plane.h"

Plane::Plane(double xDimension, double yDimension, const Vector *center, const RGB *color, const Vector *normal,
             const Vector *headup, double reflectivity) : Object(center, color, reflectivity) {
    this->xDimension = xDimension;
    this->yDimension = yDimension;
    this->normal = normal->clone();
    this->headup = headup->clone();
}

Plane::~Plane() {
    delete this->normal;
    delete this->headup;
}

void Plane::print() {
    std::cout << "Plane." << std::endl;
    std::cout << "      x dimension: " << this->xDimension << ", y dimension: " << this->yDimension << std::endl;
    std::cout << "      center: ";
    this->getCenter()->print();
    std::cout << "      color: ";
    this->getColor()->print();
    std::cout << std::endl;
    std::cout << "      normal: ";
    this->normal->print();
    std::cout << "      headup: ";
    this->headup->print();
    std::cout << "      reflectivity: " << this->getReflectivity() << std::endl;
}

Vector *Plane::intersect(const Ray *ray) const {
    std::cerr << "TODO: Implement plane intersection" << std::endl;
    return nullptr;
}

Vector *Plane::getNormal(const Vector *point) const {
    return this->normal->clone();
}
