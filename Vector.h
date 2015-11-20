//
// Class representing a vector (x, y, z) where x, y and z are doubles
//


#ifndef CS180_PROG4_VECTOR_H
#define CS180_PROG4_VECTOR_H

class Vector {
public:
    Vector(double, double, double);
    Vector(double*); // Pass [x, y, z]

    void normalize();
    void subtract(Vector* other); // this = this - other

    double length() const;
    double get(int) const;

    void print() const;

private:
    double vector[3];

};


#endif //CS180_PROG4_VECTOR_H
