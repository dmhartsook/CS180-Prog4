#include <iostream>
#include <assert.h>
#include <math.h>
#include "Vector.h"

Vector::Vector(double x, double y, double z) {
    this->vector[0] = x;
    this->vector[1] = y;
    this->vector[2] = z;
}

Vector::Vector(double *point) {
    this->vector[0] = point[0];
    this->vector[1] = point[1];
    this->vector[2] = point[2];
}

void Vector::print() const {
    std::cout << "(" << this->vector[0] << ", " << this->vector[1] << ", " << this->vector[2] << ")" << std::endl;
}

double Vector::length() const {
    return sqrt(this->vector[0] * this->vector[0]
                + this->vector[1] * this->vector[1]
                + this->vector[2] * this->vector[2]);
}

void Vector::normalize() {
    double length = this->length();
    this->vector[0] /= length;
    this->vector[1] /= length;
    this->vector[2] /= length;
}

void Vector::subtract(Vector *other) {
    this->vector[0] -= other->get(0);
    this->vector[1] -= other->get(1);
    this->vector[2] -= other->get(2);
}

double Vector::get(int i) const {
    assert(i < 3 && i >= 0);
    return this->vector[i];
}

double* Vector::toArray() {
    double* array = new double[3];
    array[0] = this->vector[0];
    array[1] = this->vector[1];
    array[2] = this->vector[2];
    return array;
}

void Vector::dot(Vector *other) {
    this->vector[0] *= other->get(0);
    this->vector[1] *= other->get(1);
    this->vector[2] *= other->get(2);
}
