/*
 * Class representing the image plane (pixels).
 * Plane is at z = 1 and is centered around the z-axis.
 * -0.5 <= x, y <= 0.5
 */

#ifndef CS180_PROG4_IMAGEPLANE_H
#define CS180_PROG4_IMAGEPLANE_H

#include "RGB.h"

class ImagePlane {
public:
    ImagePlane(int px, int py);
    ~ImagePlane();

    // Converts the pixel at (i, j) into (x, y, z) coordinates
    double*getPixelCoords(int i, int j);

    void print();

private:
    int width, height;

    // Offsets to center around z-axis
    static const double xOffset;
    static const double yOffset;
    static const int zValue = -1;

    RGB** imagePlane;
};


#endif //CS180_PROG4_IMAGEPLANE_H
