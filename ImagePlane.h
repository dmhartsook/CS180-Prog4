//
// Class representing the image plane (pixels)
//

#ifndef CS180_PROG4_IMAGEPLANE_H
#define CS180_PROG4_IMAGEPLANE_H

typedef struct RGB {
    double red;
    double green;
    double blue;
} RGB;


class ImagePlane {
public:
    ImagePlane(int width, int height);
    ~ImagePlane();

    void print();

private:
    int width, height;
    RGB** imagePlane;
};


#endif //CS180_PROG4_IMAGEPLANE_H
