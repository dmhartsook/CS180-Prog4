#ifndef CS180_PROG4_RAY_H
#define CS180_PROG4_RAY_H


#include "Vector.h"

class Ray : public Vector {
public:
    // Pass two points of the form[x, y, z]. Ray is a vector from start to end.
    Ray(double* start, double* end);
};


#endif //CS180_PROG4_RAY_H
