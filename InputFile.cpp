#include <fstream>
#include "InputFile.h"
#include "Sphere.h"
#include <iostream>
#include <assert.h>

InputFile::InputFile(const char *filename) {
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    file.ignore(10, ' ');   // ignore "camera"
    file >> cameraResolution;

    char buffer[100];

    std::string objectType;
    while (getline(file, objectType)) {
        if (objectType.compare("sphere") == 0) {
            Sphere* sphere = createSphere(file);
            this->objects.push_back(sphere);
        } else if (objectType.compare("plane") == 0) {
            std::cerr << "TODO: Create a plane" << std::endl;
        } else if (objectType.compare("light") == 0) {
            Light* light = createLight(file);
            lights.push_back(light);
        }
    }

    file.close();
}

InputFile::~InputFile() {
    objects.clear();
    lights.clear();
}

Sphere* InputFile::createSphere(std::ifstream &file) const {
    std::string attribute;
    file >> attribute;
    assert(attribute.compare("dimension") == 0);
    double dimension;
    file >> dimension;

    file >> attribute;
    assert(attribute.compare("center") == 0);
    int centerX, centerY, centerZ;
    file >> centerX;
    file >> centerY;
    file >> centerZ;
    Vector* center = new Vector(centerX, centerY, centerZ);

    file >> attribute;
    assert(attribute.compare("color") == 0);
    double red, green, blue;
    file >> red;
    file >> green;
    file >> blue;
    RGB* color = new RGB(red, green, blue);

    double reflectivity = 1.0;
    if (attribute.compare("reflectivity") == 0) {
        std::cerr << "TODO: implement reading reflective value" << std::endl;
    } else if (attribute.compare("texture") == 0) {
        std::cerr << "TODO: implement reading texture value" << std::endl;
    } else {
        // Onto the next object so move backwards so that the outer loop can determine the object type
        file.seekg(-attribute.length(), file.cur);
    }

    Sphere* sphere = new Sphere(center, color, reflectivity, dimension);

    delete center;
    delete color;

    return sphere;
}

Light* InputFile::createLight(std::ifstream &file) const {
    std::string attribute;
    file >> attribute;
    assert(attribute.compare("location") == 0);
    int locationX, locationY, locationZ;
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
