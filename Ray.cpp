#include <iostream>
#include <math.h>
#include "Ray.h"
#include "Object.h"

static const double EPSILON = .0001;

Ray::Ray(Vector start, Vector end) : Vector(end.toArray()) {
    Vector* startVector = new Vector(start.toArray());
    this->subtract(startVector);
    this->start = startVector;
}

Ray::Ray(const Ray &other) : Vector(other) {
    this->start = other.getStart()->clone();
}

Ray::~Ray() {
    delete this->start;
}

const Vector* Ray::getStart() const {
    return start;
}

void Ray::print() const {
    std::cout << "this ray:";
    Vector::print();
    std::cout << "start: ";
    this->start->print();
}


void Ray::move(double amount) {
	Vector* moveVector = this->clone();
	moveVector->normalize();
	moveVector->multiply(amount);
	this->add(moveVector);
	this->start->add(moveVector);
	delete moveVector;
}

RGB *Ray::castRay(Scene &scene) {
    return castRay(scene, 0);
}

RGB *Ray::castRay(Scene &scene, int depth) const {
    std::pair<const Vector*, const Object*> intersection = findIntersection(scene.objects);
    const Vector* intersectionPoint = intersection.first;
    const Object* intersectedObject = intersection.second;
    if (intersectionPoint != NULL) {
        return determineColor(intersectedObject, intersectionPoint, scene);
    } else {
        return NULL;
    }
}

std::pair<const Vector *, const Object *> Ray::findIntersection(std::vector<const Object *> &objects) const {
    const Vector* closestPoint = NULL;
    const Object* closestObject = NULL;
    double distanceClosest = INFINITY;
    for (int i = 0; i < objects.size(); i++) {
        const Vector* intersectionPoint = objects[i]->intersect(this);
        if (intersectionPoint != NULL) {
            double intersectDistance = this->start->distance(intersectionPoint);
            if (intersectDistance < distanceClosest) {
                closestObject = objects[i];
                closestPoint = intersectionPoint;
                distanceClosest = intersectDistance;
            }
        }

    }
    return std::make_pair(closestPoint, closestObject);
}

RGB *Ray::determineColor(const Object *object, const Vector *intersectionPoint, Scene scene) const {
    RGB* actualColor = new RGB(0, 0, 0);
    const RGB* materialColor = object->getColor();
    Vector *normal = object->getNormal(intersectionPoint);

    for (int i = 0; i < scene.lights.size(); i++) {
        Ray *lightRay = new Ray(*intersectionPoint, *(scene.lights[i]->getLocation()));
        lightRay->move(EPSILON); // Move out to prevent ray from incorrectly colliding with the object.

        const Object *intersectedObject = lightRay->intersectObject(scene.objects);

        if (intersectedObject == NULL) { // Not in shadow
            double angle = normal->angleBetween(*lightRay);

            RGB *colorFromLight = new RGB(*materialColor);
            // if cos(angle) < 0 then in shadow so multiply by 0
            colorFromLight->multiply(std::max(0.0, cos(angle)));
            colorFromLight->multiply(scene.lights[i]->getColor());

            actualColor->add(colorFromLight);

            delete colorFromLight;
        } else if (intersectedObject->getReflectivity() > 0) { // reflection

        }
    }

    return actualColor;
}

const Object *Ray::intersectObject(std::vector<const Object *> &objects) const {
    for (int i = 0; i < objects.size(); i++) {
        const Vector* intersectionPoint = objects[i]->intersect(this);
        if (intersectionPoint != NULL) {
            return objects[i];
        }
    }

    return NULL;
}
