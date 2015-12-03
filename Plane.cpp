#include <iostream>
#include "Plane.h"
#include "Ray.h"

Plane::Plane(double xDimension, double yDimension, const Vector *center, const RGB *color, const Vector *normal,
             const Vector *headup, double reflectivity) : Object(center, color, reflectivity) {
    this->xDimension = xDimension;
    this->yDimension = yDimension;
    this->normal = normal->clone();
    this->headup = headup->clone();
    Vector* right = headup->createCrossProduct(normal);
    right->normalize();
    this->rightDir = right;
}

Plane::~Plane() {
    delete this->normal;
    delete this->headup;
    delete this->rightDir;
}

void Plane::print() const {
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
    std::cout << "      rightDir: ";
    this->rightDir->print();
    std::cout << "      reflectivity: " << this->getReflectivity() << std::endl;
}

Vector *Plane::intersect(const Ray *ray) const {
    Vector* d = ray->clone();
    d->normalize();

    Vector *n = this->normal->clone();
    n->normalize();
    Vector *o = ray->getStart()->clone();
    const Vector *c = this->getCenter();

    double nDotD = n->dot(d);
    if (nDotD == 0) { // Parallel to plane
        return NULL;
    }

    o->subtract(c); // o = o - c
    n->multiply(-1); // n = -n
    double nDotOMinusC = n->dot(o); // n = -n * (o - c)

    double t = nDotOMinusC / nDotD; // t = (-n * (o - c) ) / (n * d)

    delete d;
    delete n;
    delete o;

    if (t < 0) {
        return NULL;
    }

    d = ray->clone();
    d->normalize();

    Vector* collisionPoint = ray->getStart()->clone(); // collisionPoint = o
    d->multiply(t); // d = t * d
    collisionPoint->add(d); // collisionPoint = o + t*d

    Vector* p = new Vector(*collisionPoint);
    p->subtract(c);
    double r = this->rightDir->dot(collisionPoint); // r = r * (p - c)
    double u = this->headup->dot(collisionPoint); // u = u * (p - c)

    delete d;
    delete p;

    if (r > this->xDimension/2.0 || r < this->xDimension/-2.0 ||
            u > this->yDimension/2.0 || u < this->yDimension/-2.0) { // Collision point not within actual plane
        return NULL;
    } else {
        return collisionPoint;
    }
}

Vector *Plane::getNormal(const Vector *point) const {
    return this->normal->clone();
}
