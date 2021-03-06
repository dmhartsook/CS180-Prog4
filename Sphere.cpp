#include "Sphere.h"
#include <stddef.h>
#include <iostream>
#include <cmath>
#include <assert.h>
#include "Ray.h"


bool double_equals(double a, double b, double epsilon = 0.00001) {
    return std::abs(a - b) < epsilon;
}


Sphere::Sphere(const Vector *center, const RGB *color, double reflectivity, double radius)
        : Object(center, color, reflectivity, NULL) {

    this->radius = radius;
}

Sphere::Sphere(const Vector *center, const RGB *color, double reflectivity, double radius, Texture *texture)
        : Object(center, color, reflectivity, texture) {
    this->radius = radius;
}


Vector* Sphere::intersect(const Ray *r) const {
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

    if (t < 0) {
        delete d;
        return NULL;
    }

    d->multiply(t); // d = t * d
    Vector* collisionPoint = r->getStart()->clone();
    collisionPoint->add(d);

    delete d;

    return collisionPoint; // o + td
}

Vector *Sphere::getNormal(const Vector *point) const {
    Vector* normal = new Vector(*point);
    normal->subtract(this->getCenter());
    assert(double_equals(normal->length(), this->radius)); // Ensure point is on the surface
    normal->normalize();

    return normal;
}

void Sphere::print() const {
    std::cout << "Sphere:" << std::endl;
    std::cout << "      center: ";
    this->getCenter()->print();
    if (this->getColor() != NULL) {
        std::cout << "      color: ";
        this->getColor()->print();
        std::cout << std::endl;
    }
    std::cout << "      radius: " << this->radius << std::endl;
    std::cout << "      reflectivity: " << this->getReflectivity() << std::endl;
    if (this->getTexture() != NULL) {
        std::cout << "      texture: ";
        this->getTexture()->print();
    }
}

double Sphere::findU(const Vector *point)  const {
    Vector* normal = getNormal(point);
    normal->normalize();

    // u = arctan(normalZ / normalX) / 2PI + 0.5
    double u = atan2(normal->get(2), normal->get(0));
    u /= (2 * M_PI);
    u += 0.5;

    delete normal;
    return u;
}

double Sphere::findV(const Vector *point) const {
    Vector* normal = getNormal(point);
    normal->normalize();

    // v = .5 − arcsin(normalY)/PI
    double v = 0.5 - (asin(normal->get(1))) / M_PI;

    delete normal;
    return v;
}
