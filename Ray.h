#ifndef CS180_PROG4_RAY_H
#define CS180_PROG4_RAY_H

#include "Vector.h"
#include "RGB.h"
#include "Scene.h"
#include "Object.h"

class Ray : public Vector {
public:
    // Pass two points of the form[x, y, z]. Ray is a vector from start to end.
    Ray(Vector start, Vector end);
    Ray(const Ray&);
    ~Ray();

    /*
     * Returns a new RGB* containing the color of the first spot the ray collides with.
     * Depth is the recursion depth of the call, maxes out at MAX_CASTING_DEPTH
     * Returns Null if the ray does not collide with anything.
     */
    RGB* castRay(Scene& scene, int depth) const;

    // Moves the ray by amount. Adjusts the start of the ray.
    void moveStart(double amount);

    const Vector* getStart() const;

    void print() const;

    std::pair<const Vector *, const Object *> intersectObject(std::vector<const Object *> &objects) const;

private:
    static const int MAX_CASTING_DEPTH = 8;
    Vector* start;

    /*
     * Returns the intersected object and intersection point if the ray intersects any object
     * in the vector of objects.
     * Returns NULL if the ray does not intersect any objects.
     */
//    std::pair<const Vector *, const Object *> intersectObject(std::vector<const Object *> &objects) const;

    /*
     * Finds the interesection between the ray and the closest object.
     * Returns the intersection point, which is a new vector and must be deleted.
     * Also returns the object that was intersected.
     */
    std::pair<const Vector *, const Object *> findIntersection(std::vector<const Object *> &objects) const;

    /*
     * Determines the color of the object at the intersectionPoint from the lights.
     * Sum(lightColor*materialColor*cos(angleFromNormalToLight).
     * Returns a new RGB object that must be destroyed.
     */
    RGB *determineColor(const Object *object, const Vector *intersectionPoint, Scene scene, int depth) const;
};


#endif //CS180_PROG4_RAY_H
