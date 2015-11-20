#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include "ImagePlane.h"


int main(int argc, char** argv) {
    const double eye[3] = {0.0, 0.0, 0.0};
    const int imagePlaneSize = 640;
    ImagePlane* imagePlane = new ImagePlane(imagePlaneSize, imagePlaneSize);

    delete imagePlane;


//    double vec[3] = {5.1, 5.0, 3};
//    Vector* v = new Vector(vec);
//    Vector* v2 = new Vector(3, 4, 5);
//    v->print();
//    std::cout << v->get(0) << std::endl;
//
//    v->subtract(v2);
//    v->print();

//    double start[3] = {1.0, 0.5, 0.25};
//    Ray* ray = new Ray(start, vec);
//    ray->print();

    return 0;
}