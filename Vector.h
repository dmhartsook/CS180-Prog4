//
// Class representing a vector (x, y, z) where x, y and z are doubles
//


#ifndef CS180_PROG4_VECTOR_H
#define CS180_PROG4_VECTOR_H

class Vector {
public:
    Vector(double, double, double);
    Vector(double*); // Pass [x, y, z]
    Vector(const Vector&);

    void normalize();
    Vector* clone() const;
    void add(const Vector* other); // this = this + other
    void subtract(const Vector *other); // this = this - other
    double dot(const Vector *other) const;
    void multiply(double scalar);   // Multiplies the vector by the given scalar

    double length() const;
    double get(int) const;

    // Creates a new double array with the values in the vector
    double* toArray() const;
    void print() const;


private:
    double vector[3];

};


#endif //CS180_PROG4_VECTOR_H
