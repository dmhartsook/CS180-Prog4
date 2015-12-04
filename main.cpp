#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "ImagePlane.h"
#include "InputFile.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include <utility>
#include "Light.h"
#include "InputFile.h"
#include "Scene.h"
#include <vector>

static const char *const DEFAULT_IMAGE_FILENAME = "scene.ppm";
static const RGB BACKGROUND_COLOR(0, 0, 0);

void writePpm(const ImagePlane *, const char *filename);

int main(int argc, char** argv) {
    Vector eye = Vector(0, 0, 0);

    InputFile* inputFile;
    char* filename;
    if (argc > 1) {
        inputFile = new InputFile(argv[1]);
        filename = strtok(argv[1], ".");
        strcat(filename, ".ppm");
    } else {
        std::cerr << "Please specify an input file to read the scene data from." << std::endl;
        return 0;
    }

    Scene scene;
    scene.objects = inputFile->getObjects();
    scene.lights = inputFile->getLights();

    const int imagePlaneSize = inputFile->getCameraResolution();
//    const int imagePlaneSize = 200;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

//    for (int i = 0; i < scene.objects.size(); i++){
//        scene.objects[i]->print();
//    }
//
//    const Object* plane = scene.objects[0];
//    Vector start(0,0,0);
//    Vector end(0, 0, -5);
//    Ray* ray = new Ray(start, end);
//    Vector* pt = plane->intersect(ray);
//
//    if (pt != NULL) {
//        pt->print();
//    } else {
//        std::cout << "NULL" << std::endl;
//    }
//
//    return 0;

//    RGB* sphereColor = new RGB(1, 1, 1);
//    Vector* sphereCenter = new Vector (0, 0, -5);
//    const Sphere* sphere = new Sphere(sphereCenter, sphereColor, 1, 1);
//    delete sphereColor;
//    delete sphereCenter;
//

//    Vector* v1 = new Vector(1, 1, 0);
//    Vector* v2 = new Vector(3, 0, 0);
//    std::cout << v1->distance(v2) << std::endl;
//
//    return  0;

//    RGB* r1 = new RGB(.2, .4, .7);
//    RGB* r2 = new RGB(.1, .6, .5);
//    r1->add(r2);
//    r1->print();
//    std::cout << std::endl;
//
//    return 0;

//    Vector start = Vector(4, 0, 0);
//    Vector end = Vector(0,0, -4);
//    Ray* ray = new Ray(start, end);
//    std::cout << "original ray: ";
//    ray->print();
//    Vector point = Vector(0, 0, -4);
//    std::cout << "reflected at point ";
//    point.print();
//    Vector* normal = sphere->getNormal(&point);
//    Vector* reflectedDir = ray->createReflectedVector(normal);
//    std::cout << "reflectedDir: ";
//    reflectedDir->print();
//
//    reflectedDir->add(&point);
//
//    std::cout << "reflect: ";
//    Ray* reflect = new Ray(point, *reflectedDir);
//    reflect->print();
//
//    return 0;

//    RGB* lightColor = new RGB(.7, .7, 1);
//    Vector* lightLocation = new Vector(1, 0,-4);
//    const Light* light = new Light(lightLocation, lightColor);
//    delete lightColor;
//    delete lightLocation;
//
//    Vector center(0, -1, -5);
//    Vector normal(0, 1, 0);
//    Vector headup(0, 1, 0);
//    RGB color(.5, .5, .5);
//    Plane* plane = new Plane(4, 4, &center, &color, &normal, &headup, 1);
//
//    std::cout << "cross headup and normal: ";
//    Vector* cross = headup.createCrossProduct(&normal);
//    cross->print();
//
//    std::vector<const Object*> objects;
//    objects.push_back(plane);
//
//    Vector point(0, .5, -7);
//    Ray *lightRay = new Ray(point, *(light->getLocation()));
//
//    std::cout << "light ray: ";
//    lightRay->print();
//
//    std::pair<const Vector *, const Object *> intersectionBlockingLight =
//            lightRay->intersectObject(objects);
//    const Vector* pointBlockingLight = intersectionBlockingLight.first;
//    const Object* intersected = intersectionBlockingLight.second;
//
//    if (intersected != NULL) {
//        intersected->print();
//    } else {
//        std::cout << "NULL " << std::endl;
//    }
//
//    return 0;


    for (int i = 0; i < imagePlaneSize; i++) {
        for (int j = 0; j < imagePlaneSize; j++) {
            double* pixel = imagePlane->getPixelCoords(i, j);
            Vector pixelVector = Vector(pixel);
            Ray* pixelRay = new Ray(eye, pixelVector);

            RGB* actualColor = pixelRay->castRay(scene, 0);
            if (actualColor == NULL) {
                actualColor = new RGB(BACKGROUND_COLOR);
            }
            imagePlane->setPixelColor(i, j, actualColor);

            delete actualColor;
            delete pixelRay;
            delete[] pixel;
        }
    }

    // TODO: Remove default name
    writePpm(imagePlane, DEFAULT_IMAGE_FILENAME);
//    writePpm(imagePlane, filename);

    delete imagePlane;
    delete inputFile;

    return 0;
}


void writePpm(const ImagePlane *imagePlane, const char *filename) {
    std::ofstream image;
    image.open(filename, std::ios::binary);

    image << "P3" << "\n"
        << imagePlane->getWidth() << " " << imagePlane->getHeight() << "\n"
        << "255\n";

    for (int j = imagePlane->getHeight() - 1; j >= 0; j--) {
        for (int i = 0; i < imagePlane->getWidth(); i++)  {
            const RGB *color = imagePlane->getPixelColor(i, j);
            int* colorVals = color->convertTo255Values();

            image << colorVals[0] << " " <<  colorVals[1] << " " << colorVals[2] << "  ";

            delete[] colorVals;
        }
        image << "\n";
    }

    image.close();
}
