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


void Ray::moveStart(double amount) {
	Vector* moveVector = this->clone();
	moveVector->normalize();
	moveVector->multiply(amount);
	this->start->add(moveVector);
	delete moveVector;
}

RGB *Ray::castRay(Scene &scene, int depth) const {
    if (depth >= MAX_CASTING_DEPTH) {
        return NULL;
    }

    std::pair<const Vector*, const Object*> intersection = findIntersection(scene.objects);
    const Vector* intersectionPoint = intersection.first;
    const Object* intersectedObject = intersection.second;
    if (intersectionPoint != NULL) {
        return determineColor(intersectedObject, intersectionPoint, scene, depth);
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

RGB *Ray::determineColor(const Object *object, const Vector *intersectionPoint, Scene scene, int depth) const {
    RGB* actualColor = new RGB(0, 0, 0);
    const RGB* materialColor = object->getColor();
    Vector *normal = object->getNormal(intersectionPoint);

    for (int i = 0; i < scene.lights.size(); i++) {
    	const Vector* lightLocation = scene.lights[i]->getLocation();
        Ray *lightRay = new Ray(*intersectionPoint, *lightLocation);
        lightRay->moveStart(EPSILON); // Move out to prevent ray from incorrectly colliding with the object.

        std::pair<const Vector *, const Object *> intersectionBlockingLight =
        		lightRay->intersectObject(scene.objects);
        const Vector* pointBlockingLight = intersectionBlockingLight.first;
        const Object* objectBlockingLight = intersectionBlockingLight.second;

        if (pointBlockingLight != NULL) {
        	// Intersected an object on the way to the light but make sure the object isn't at the light
        	// i.e. a light in a plane: the plane shouldn't prevent light from shining
        	double distanceToLight = pointBlockingLight->distance(lightLocation);
        	if (distanceToLight < 2.91) {
        		objectBlockingLight->print();
        		scene.lights[i]->print();
        		std::cout << "distance: " << distanceToLight << std::endl;
        	}
        	if (distanceToLight < .01) {
        		// Intersection at the light - pretend there was no intersection
        		objectBlockingLight = NULL;
        		pointBlockingLight = NULL;
        	}
        }

        if (objectBlockingLight == NULL ) { // Not in shadow
            double angle = normal->angleBetween(*lightRay);

            RGB *colorFromLight = new RGB(*materialColor);
            // if cos(angle) < 0 then in shadow so multiply by 0
            colorFromLight->multiply(std::max(0.0, cos(angle)));
            colorFromLight->multiply(scene.lights[i]->getColor());

            actualColor->add(colorFromLight);

            delete colorFromLight;
        }
        if (object->getReflectivity() > 0) { // reflection
            Vector *reflectedVector = this->createReflectedVector(normal);
            reflectedVector->add(intersectionPoint); // move it to start at the intersectionBlockingLight point
            Ray* reflectedRay = new Ray(*intersectionPoint, *reflectedVector);
            reflectedRay->moveStart(EPSILON);
            RGB* reflectionColor = reflectedRay->castRay(scene, depth + 1);

            if (reflectionColor != NULL) {
                reflectionColor->multiply(object->getReflectivity());
                actualColor->add(reflectionColor);
            }

            delete reflectedRay;
            delete reflectedVector;
            delete reflectionColor;
        }
    }

    return actualColor;
}

std::pair<const Vector *, const Object *> Ray::intersectObject(std::vector<const Object *> &objects) const {
	const Vector* intersectionPoint = NULL;

	for (int i = 0; i < objects.size(); i++) {
        intersectionPoint = objects[i]->intersect(this);
        if (intersectionPoint != NULL) {
            return std::make_pair(intersectionPoint, objects[i]);
        }
    }

	const Object* objectNull = NULL;
    return std::make_pair(intersectionPoint, objectNull);
}
