//
// Abstract class for objects in the scene.
//

#ifndef CS180_PROG4_OBJECT_H
#define CS180_PROG4_OBJECT_H


#include "Ray.h"
#include "RGB.h"

class Object {
public:
    Object(const Vector *center, const RGB *color, double reflectivity);
    virtual ~Object();

    const RGB* getColor();
    const Vector* getCenter();

    // Returns the closest collision point if there is one and NULL if there is no collision
    virtual Vector * intersect(Ray *) = 0;

private:
    Vector* center;
    RGB* color;
    double reflectivity;
};


#endif //CS180_PROG4_OBJECT_H
