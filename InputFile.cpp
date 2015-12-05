#include <fstream>
#include "InputFile.h"
#include "Sphere.h"
#include "Plane.h"
#include "Texture.h"
#include <iostream>
#include <assert.h>

const std::array<std::string, 3> InputFile::SCENE_OBJECT_TYPES = {"sphere", "light", "plane"};

InputFile::InputFile(const char *filename) {
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    file.ignore(10, ' ');   // ignore "camera"
    file >> cameraResolution;

    std::string objectType;
    while (getline(file, objectType)) {
        if (objectType.compare("sphere") == 0) {
            Sphere* sphere = createSphere(file);
            this->objects.push_back(sphere);
        } else if (objectType.compare("plane") == 0) {
            Plane* plane = createPlane(file);
            this->objects.push_back(plane);
        } else if (objectType.compare("light") == 0) {
            Light* light = createLight(file);
            this->lights.push_back(light);
        }
    }

    file.close();
}

InputFile::~InputFile() {
    objects.clear();
    lights.clear();
}

Sphere* InputFile::createSphere(std::ifstream &file) const {
    double dimension;
    Vector* center = NULL;
    RGB* color = NULL;
    double reflectivity = 0.0;
    Texture* texture = NULL;

    std::string attribute;
    file >> attribute;

    // while there are still attributes to read (not onto next object)
    while (std::find(this->SCENE_OBJECT_TYPES.begin(), this->SCENE_OBJECT_TYPES.end(), attribute)
           == this->SCENE_OBJECT_TYPES.end()) {
        if (attribute.compare("dimension") == 0) {
            file >> dimension;
        } else if (attribute.compare("center") == 0) {
            double centerX, centerY, centerZ;
            file >> centerX;
            file >> centerY;
            file >> centerZ;
            center = new Vector(centerX, centerY, centerZ);
        } else if (attribute.compare("color") == 0) {
            double red, green, blue;
            file >> red;
            file >> green;
            file >> blue;
            color = new RGB(red, green, blue);
        } else if (attribute.compare("reflectivity") == 0) {
            file >> reflectivity;
        } else if (attribute.compare("texture") == 0) {
            char textureFile[50];
            file >> textureFile;
            texture = new Texture(textureFile);
        }
        file >> attribute;
    }

    // Onto the next object so move backwards so that the outer loop can determine the object type
    file.seekg(-1 * attribute.length(), file.cur);

    Sphere* sphere = new Sphere(center, color, reflectivity, dimension, texture);

    delete center;
    delete color;

    return sphere;
}

Light* InputFile::createLight(std::ifstream &file) const {
    std::string attribute;
    file >> attribute;
    assert(attribute.compare("location") == 0);
    double locationX, locationY, locationZ;
    file >> locationX;
    file >> locationY;
    file >> locationZ;
    Vector* location = new Vector(locationX, locationY, locationZ);

    file >> attribute;
    assert(attribute.compare("color") == 0);
    double red, green, blue;
    file >> red;
    file >> green;
    file >> blue;
    RGB* color = new RGB(red, green, blue);

    Light* light = new Light(location, color);

    delete location;
    delete color;

    return light;
}

std::vector<const Object *> InputFile::getObjects() const {
    return this->objects;
}

std::vector<const Light *> InputFile::getLights() const {
    return this->lights;
}

int InputFile::getCameraResolution() const {
    return this->cameraResolution;
}

Plane * InputFile::createPlane(std::ifstream &file) {
    double xLength, yLength;
    Vector* center;
    Vector* normal;
    Vector* headup;
    RGB* color;
    double reflectivity = 0.0;

    std::string attribute;
    file >> attribute;


    // while there are still attributes to read (not onto next object)
    while (std::find(this->SCENE_OBJECT_TYPES.begin(), this->SCENE_OBJECT_TYPES.end(), attribute)
           == this->SCENE_OBJECT_TYPES.end()) {
        if (attribute.compare("dimension") == 0) {
            file >> xLength;
            file >> yLength;
        } else if (attribute.compare("center") == 0) {
            double centerX, centerY, centerZ;
            file >> centerX;
            file >> centerY;
            file >> centerZ;
            center = new Vector(centerX, centerY, centerZ);
        } else if (attribute.compare("normal") == 0) {
            double normalX, normalY, normalZ;
            file >> normalX;
            file >> normalY;
            file >> normalZ;
            normal = new Vector(normalX, normalY, normalZ);
        } else if (attribute.compare("headup") == 0) {
            double headupX, headupY, headupZ;
            file >> headupX;
            file >> headupY;
            file >> headupZ;
            headup = new Vector(headupX, headupY, headupZ);
        } else if (attribute.compare("color") == 0) {
            double red, green, blue;
            file >> red;
            file >> green;
            file >> blue;
            color = new RGB(red, green, blue);
        } else if (attribute.compare("reflectivity") == 0) {
            file >> reflectivity;
        } else if (attribute.compare("texture") == 0) {
            std::cerr << "TODO: implement reading texture value" << std::endl;
        }
        file >> attribute;
    }

    // Onto the next object so move backwards so that the outer loop can determine the object type
    file.seekg(-attribute.length(), file.cur);

    Plane* plane = new Plane(xLength, yLength, center, color, normal, headup, reflectivity);

    delete center;
    delete color;
    delete normal;
    delete headup;

    return plane;
}
