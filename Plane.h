//
// Represents a plane in the scene
//

#ifndef CS180_PROG4_PLANE_H
#define CS180_PROG4_PLANE_H


#include "Object.h"

class Plane : public Object {

public:
    Plane(double xDimension,
          double yDimension,
          const Vector *center,
          const RGB *color,
          const Vector* normal,
          const Vector* headup,
          double reflectivity);
    ~Plane();

    Vector* intersect(const Ray *) const;
    Vector* getNormal(const Vector *point) const;

    void print();

private:
    double xDimension;
    double yDimension;
    const Vector* normal;
    const Vector* headup;
};


#endif //CS180_PROG4_PLANE_H
