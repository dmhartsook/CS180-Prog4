//
// Abstract class for objects in the scene.
//

#ifndef CS180_PROG4_OBJECT_H
#define CS180_PROG4_OBJECT_H


#include "RGB.h"

class Object {
public:
    Object(double* center, RGB color);
    virtual ~Object() {};

    RGB getColor();

private:
    double center[3];
    RGB color;

};


#endif //CS180_PROG4_OBJECT_H
