#include "Sphere.h"
#include <stddef.h>
#include <iostream>
#include <math.h>

Sphere::Sphere(Vector center, const RGB &color, double reflectivity, double radius)
        : Object(center, color, reflectivity) {

    this->radius = radius;
}



Vector* Sphere::intersect(Ray *r) {
    Vector* d = r->clone();
    d->normalize();

    Vector* o = r->getStart()->clone();
    o->subtract(this->getCenter());     // o = o - c

    double b = d->dot(o); // b = d * (o - c)

    double c = o->dot(o); // c = o * o
    c -= this->radius * this->radius;

    double det = b*b - c;

    delete o;

    double t;
    if (det > 0) {
        // two solutions
        double t1 = -b + sqrt(det);
        double t2 = -b - sqrt(det);
        if (t2 > 0) {
            t = t2;
        } else {
            t = t1;
        }
    } else if (det == 0) {
        // one solution
        t = -b;
    } else {
        // no solution
        return NULL;
    }

    d->multiply(t); // d = t * d
    Vector* collisionPoint = r->getStart()->clone();
    collisionPoint->add(d);

    delete d;

    return collisionPoint;
}
