#include <iostream>
#include "Ray.h"

Ray::Ray(Vector start, Vector end) : Vector(end.toArray()) {
    Vector* startVector = new Vector(start.toArray());
    this->subtract(startVector);
    this->start = startVector;
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
	Vector amountVector(amount, amount, amount);
	this->add(&amountVector);
	this->start->add(&amountVector);
}
