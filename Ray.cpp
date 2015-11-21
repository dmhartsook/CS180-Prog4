#include "Ray.h"

Ray::Ray(Vector start, Vector end) : Vector(end.toArray()) {
    this->subtract(&start);
}
