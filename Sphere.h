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

    // Returns the computed parameter u for the sphere at the given point
    double findU(const Vector* point) const;

    // Returns the computed parameter v for the sphere at the given point
    double findV(const Vector* point) const;

    void print() const;

private:
    double radius;

};


#endif //CS180_PROG4_SPHERE_H
