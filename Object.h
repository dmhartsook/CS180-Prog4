//
// Abstract class for objects in the scene.
//

#ifndef CS180_PROG4_OBJECT_H
#define CS180_PROG4_OBJECT_H


#include "RGB.h"

class Object {
public:
    Object(double *center, RGB color, double reflectivity);
    virtual ~Object() { };

    RGB getColor();
    double* getCenter();

private:
    double center[3];
    RGB color;
    double reflectivity;
};


#endif //CS180_PROG4_OBJECT_H
