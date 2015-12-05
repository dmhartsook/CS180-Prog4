//
// Abstract class for objects in the scene.
//

#ifndef CS180_PROG4_OBJECT_H
#define CS180_PROG4_OBJECT_H

#include "RGB.h"
#include "Vector.h"
#include "Texture.h"

class Ray;

class Object {
public:
    Object(const Vector *center, const RGB *color, double reflectivity, Texture* texture);
    virtual ~Object();

    const RGB* getColor() const;
    const Vector* getCenter() const;
    double getReflectivity() const;
    const Texture* getTexture() const;

    /*
     * Returns the closest collision point if there is one and NULL if there is no collision.
     * This is a new Vector that will need to be deleted.
     */
    virtual Vector * intersect(const Ray *) const = 0;

    /*
     * Returns a new vector representing the vector normal to the object at the specified point.
     * The point must be on the surface of the object.
     */
    virtual Vector*getNormal(const Vector *point) const = 0;

    virtual void print() const {};

private:
    Vector* center;
    RGB* color;
    double reflectivity;
    Texture* texture;
};


#endif //CS180_PROG4_OBJECT_H
