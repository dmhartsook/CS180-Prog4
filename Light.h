//
// Represents a light at the specified location emitting the specified color.
//

#ifndef CS180_PROG4_LIGHT_H
#define CS180_PROG4_LIGHT_H


#include "Vector.h"
#include "RGB.h"

class Light {
public:
    // Copies the given objects and saves pointers to the copies.
    Light(Vector* location, RGB* color);
    ~Light();

    const Vector* getLocation() const;
    const RGB* getColor() const;

private:
    Vector* location;
    RGB* color;
};


#endif //CS180_PROG4_LIGHT_H
