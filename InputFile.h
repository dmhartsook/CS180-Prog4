//
// Class representing an input file. Used to read the file and create the objects in it.
//

#ifndef CS180_PROG4_INPUTFILE_H
#define CS180_PROG4_INPUTFILE_H


#include <vector>
#include "Object.h"
#include "Light.h"
#include "Sphere.h"

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
    int cameraResolution;
    std::vector<const Object*> objects;
    std::vector<const Light*> lights;

    Sphere * createSphere(std::ifstream &file) const;

    Light *createLight(std::ifstream &file) const;
};


#endif //CS180_PROG4_INPUTFILE_H
