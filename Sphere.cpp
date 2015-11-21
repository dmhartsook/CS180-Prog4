#include "Sphere.h"

Sphere::Sphere(double *center, const RGB &color, double reflectivity, double radius)
        : Object(center, color, reflectivity) {

    this->radius = radius;
}