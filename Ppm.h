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
    ~Ppm();

    // 0 <= u,v <= 1. u and v are scaled by width and height, respectively to return correct color
    const RGB* getColor(double u, double v) const;

    static void writePpm(const ImagePlane *, const char *filename);

    void print() const;

private:
    int width;
    int height;
    RGB*** image; // RGB* image[width][height]

    void readInImage(const char *filename);
};


#endif //CS180_PROG4_PPM_H
