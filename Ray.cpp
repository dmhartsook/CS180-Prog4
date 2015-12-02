#include <iostream>
#include "Ray.h"

Ray::Ray(Vector start, Vector end) : Vector(end.toArray()) {
    Vector* startVector = new Vector(start.toArray());
    this->subtract(startVector);
    this->start = startVector;
}

Ray::Ray(const Ray &other) : Vector(other) {
    this->start = other.getStart()->clone();
}

Ray::~Ray() {
    delete this->start;
}

const Vector* Ray::getStart() const {
    return start;
}

void Ray::print() const {
    std::cout << "this ray:";
    Vector::print();
    std::cout << "start: ";
    this->start->print();
}


void Ray::move(double amount) {
	Vector* moveVector = this->clone();
	moveVector->normalize();
	moveVector->multiply(amount);
	this->add(moveVector);
	this->start->add(moveVector);
	delete moveVector;
}
