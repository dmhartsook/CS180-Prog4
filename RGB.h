//
// Created by Deanna Hartsook on 11/22/15.
//

#ifndef CS180_PROG4_RGB_H
#define CS180_PROG4_RGB_H


class RGB {
public:
    // Colors should be specified between 0 (black) and 1 (white)
    RGB(double, double, double);
    RGB(const RGB&);

    void setColors(double r, double g, double b);
    // Multiplies RGB by value. Ensures the values stay between 0 and 1.
    void multiply(double value);
    // Multiplies each component of each RGB
    void multiply(const RGB* other);

    double getRed() const;
    double getGreen() const;
    double getBlue() const;

    // Creates a new int[3] with the RGB values between 0 and 255. Must delete the int*.
    int* convertTo255Values() const;

    void print() const;

private:
    double red;
    double green;
    double blue;

    /*
     * Sets passed value to 0 if it is less than 0
     * Sets passed value to 1 if it is greater than 1
     */
    void boundColor(double& color);
};


#endif //CS180_PROG4_RGB_H
