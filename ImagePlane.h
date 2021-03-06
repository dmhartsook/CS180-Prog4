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

    void setPixelColor(int j, int i, const RGB * color);

    // Converts the pixel at (i, j) into (x, y, z) coordinates
    double* getPixelCoords(int i, int j) const;
    const RGB* getPixelColor(int i, int j) const;
    int getWidth() const;
    int getHeight() const;

    void print() const;

private:
    int width, height;

    // Offsets to center around z-axis
    static const double xOffset;
    static const double yOffset;
    static const int zValue = -1;

    RGB*** imagePlane; // RGB* imagePlane[width][height]
};


#endif //CS180_PROG4_IMAGEPLANE_H
