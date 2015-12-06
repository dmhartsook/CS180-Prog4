//
// Class for reading and writing PPM files
//

#ifndef CS180_PROG4_PPM_H
#define CS180_PROG4_PPM_H

#include "ImagePlane.h"
#include "RGB.h"
#include <utility>

class Ppm {
public:
    Ppm(const char* filename);
    Ppm(const Ppm&);
    static void writePpm(const ImagePlane *, const char *filename);

private:
    int width;
    int height;
    RGB*** image; // RGB* image[width][height]

    void readInImage(const char *filename);
};


#endif //CS180_PROG4_PPM_H
