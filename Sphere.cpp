#include "Sphere.h"

Sphere::Sphere(Vector center, const RGB &color, double reflectivity, double radius)
        : Object(center, color, reflectivity) {

    this->radius = radius;
}

bool Sphere::intersect(Ray *ray) {
    return false;
}
