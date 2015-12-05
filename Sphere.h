//
// Created by Deanna Hartsook on 11/20/15.
//

#ifndef CS180_PROG4_SPHERE_H
#define CS180_PROG4_SPHERE_H


#include "Object.h"
#include "RGB.h"

class Sphere : public Object {
public:
    // Copies and saves the center and color. Sets texture to null.
    Sphere(const Vector *center, const RGB *color, double reflectivity, double radius);
    Sphere(const Vector *center, const RGB *color, double reflectivity, double radius, Texture* texture);

    Vector * intersect(const Ray *) const;
    Vector*getNormal(const Vector *point) const;

    void print() const;

private:
    double radius;

};


#endif //CS180_PROG4_SPHERE_H
