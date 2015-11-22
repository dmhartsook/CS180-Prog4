#include "Ray.h"

Ray::Ray(Vector start, Vector end) : Vector(end.toArray()) {
    Vector* startVector = new Vector(start.toArray());
    this->subtract(startVector);
    this->start = startVector;
}

Ray::~Ray() {
    delete this->start;
}

const Vector* Ray::getStart() {
    return start;
}
