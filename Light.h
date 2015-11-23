//
// Represents a light at the specified location emitting the specified color.
//

#ifndef CS180_PROG4_LIGHT_H
#define CS180_PROG4_LIGHT_H


#include "Vector.h"
#include "RGB.h"

class Light {
public:
    Light(Vector* location, RGB* color);
    ~Light();

private:
    Vector* location;
    RGB* color;

};


#endif //CS180_PROG4_LIGHT_H
