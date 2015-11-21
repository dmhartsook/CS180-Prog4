//
// Abstract class for objects in the scene.
//

#ifndef CS180_PROG4_OBJECT_H
#define CS180_PROG4_OBJECT_H


#include "Ray.h"
#include "RGB.h"

class Object {
public:
    Object(Vector center, RGB color, double reflectivity);
    virtual ~Object();

    RGB getColor();
    Vector getCenter();

    virtual bool intersect(Ray) = 0;

private:
    Vector* center;
    RGB color;
    double reflectivity;
};


#endif //CS180_PROG4_OBJECT_H
