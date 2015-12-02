//
// Class representing a vector (x, y, z) where x, y and z are doubles
//


#ifndef CS180_PROG4_VECTOR_H
#define CS180_PROG4_VECTOR_H

class Vector {
public:
    Vector(double, double, double);
    Vector(double*); // Pass [x, y, z
    Vector(const Vector&);

    /*
     * Creates a new vector (that must be destroyed) that is the reflected direction of this vector around the passed
     * normal vector.
     */
    Vector* createReflectedVector(const Vector *normal) const;

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

    // Returns the angle between this and the passed vector in RADIANS
    double angleBetween(Vector) const;

    // Calculates the distance from this vector to the passed vectorr
    double distance(const Vector *other) const;

private:
    double vector[3];

};


#endif //CS180_PROG4_VECTOR_H
