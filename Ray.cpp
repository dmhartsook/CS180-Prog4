#include "Ray.h"

Ray::Ray(double * start, double *end) : Vector(end) {
    Vector* startV = new Vector(start);
    this->subtract(startV);
}
