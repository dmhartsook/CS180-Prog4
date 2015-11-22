//
// Created by Deanna Hartsook on 11/20/15.
//

#ifndef CS180_PROG4_SPHERE_H
#define CS180_PROG4_SPHERE_H


#include "Object.h"

class Sphere : public Object {
public:
    Sphere(Vector center, const RGB &color, double reflectivity, double radius);

    Vector * intersect(Ray *);

private:
    double radius;

};


#endif //CS180_PROG4_SPHERE_H
