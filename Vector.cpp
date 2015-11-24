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

Vector::Vector(const Vector &other) {
    this->vector[0] = other.get(0);
    this->vector[1] = other.get(1);
    this->vector[2] = other.get(2);
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

Vector* Vector::clone() const {
    return new Vector(this->toArray());
}

void Vector::add(const Vector *other) {
    this->vector[0] += other->get(0);
    this->vector[1] += other->get(1);
    this->vector[2] += other->get(2);
}

void Vector::subtract(const Vector *other) {
    this->vector[0] -= other->get(0);
    this->vector[1] -= other->get(1);
    this->vector[2] -= other->get(2);
}

double Vector::get(int i) const {
    assert(i < 3 && i >= 0);
    return this->vector[i];
}

double* Vector::toArray() const {
    double* array = new double[3];
    array[0] = this->vector[0];
    array[1] = this->vector[1];
    array[2] = this->vector[2];
    return array;
}

double Vector::dot(const Vector *other) const {
    double dotProduct = this->vector[0] * other->get(0);
    dotProduct += this->vector[1] * other->get(1);
    dotProduct += this->vector[2] * other->get(2);
    return  dotProduct;
}

void Vector::multiply(double scalar) {
    this->vector[0] *= scalar;
    this->vector[1] *= scalar;
    this->vector[2] *= scalar;
}

double Vector::angleBetween(Vector other) const {
    Vector* vector1 = this->clone();
    vector1->normalize();
    other.normalize();

    double angle = acos(vector1->dot(&other));

    delete vector1;
    return angle;
}

double Vector::distance(const Vector *other) const {
    double dx = other->get(0) - this->vector[0];
    double dy = other->get(1) - this->vector[1];
    double dz = other->get(2) - this->vector[2];
    return sqrt(dx*dx + dy*dy + dz*dz);
}
