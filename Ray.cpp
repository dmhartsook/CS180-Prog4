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
        Ray *lightRay = getLightRay(intersectionPoint, scene.lights[i]);
        const Object* objectBlockingLight = lightRay->intersectObject(scene.objects);

        if (objectBlockingLight == NULL ) { // Not in shadow
            RGB *colorFromLight = getColorFromLight(materialColor, normal, lightRay, scene.lights[i]);
            actualColor->add(colorFromLight);
            delete colorFromLight;
        }
        if (object->getReflectivity() > 0) { // reflection
            RGB* reflectionColor = getColorFromReflection(normal, intersectionPoint, scene, depth);

            if (reflectionColor != NULL) {
                reflectionColor->multiply(object->getReflectivity());
                actualColor->add(reflectionColor);
            }

            delete reflectionColor;
        }

        delete lightRay;
    }

    return actualColor;
}

Ray *Ray::getLightRay(const Vector *intersectionPoint, const Light *const &light) const {
    const Vector* lightLocation = light->getLocation();
    Ray *lightRay = new Ray(*intersectionPoint, *lightLocation);
    lightRay->moveStart(EPSILON); // Move out to prevent ray from incorrectly colliding with the object.

    return lightRay;
}

RGB* Ray::getColorFromReflection(const Vector* normal, const Vector* intersectionPoint, Scene& scene, int depth) const {
    Vector *reflectedVector = this->createReflectedVector(normal);
    reflectedVector->add(intersectionPoint); // move it to start at the intersectionBlockingLight point
    Ray* reflectedRay = new Ray(*intersectionPoint, *reflectedVector);
    reflectedRay->moveStart(EPSILON);
    RGB* reflectionColor = reflectedRay->castRay(scene, depth + 1);

    delete reflectedRay;
    delete reflectedVector;

    return reflectionColor;
}

RGB *Ray::getColorFromLight(const RGB *materialColor, const Vector *normal, const Ray *lightRay,
                            const Light *const &light) const {
    double angle = normal->angleBetween(*lightRay);

    RGB *colorFromLight = new RGB(*materialColor);
    // if cos(angle) < 0 then in shadow so multiply by 0
    colorFromLight->multiply(std::__1::max(0.0, cos(angle)));
    colorFromLight->multiply(light->getColor());
    return colorFromLight;
}

const Object * Ray::intersectObject(std::vector<const Object *> &objects) const {
	const Vector* intersectionPoint = NULL;

	for (int i = 0; i < objects.size(); i++) {
        intersectionPoint = objects[i]->intersect(this);
        if (intersectionPoint != NULL) {
            return objects[i];
        }
    }

    return NULL;
}
