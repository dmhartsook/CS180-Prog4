//
// Class representing an input file. Used to read the file and create the objects in it.
//

#ifndef CS180_PROG4_INPUTFILE_H
#define CS180_PROG4_INPUTFILE_H

#include <array>
#include <vector>
#include "Object.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

class InputFile {
public:
    /*
     * Reads the file and creates the needed objects.
     * Assumes the camera is listed first, followed by objects, followed by lights.
     */
    InputFile(const char* filename);
    ~InputFile();

    std::vector<const Object*> getObjects() const;
    std::vector<const Light*> getLights() const;
    int getCameraResolution() const;

private:
    static const std::array<std::string, 3> SCENE_OBJECT_TYPES;
    int cameraResolution;
    std::vector<const Object*> objects;
    std::vector<const Light*> lights;

    Sphere * createSphere(std::ifstream &file) const;

    Light *createLight(std::ifstream &file) const;

    Plane * createPlane(std::ifstream &file);
};


#endif //CS180_PROG4_INPUTFILE_H
