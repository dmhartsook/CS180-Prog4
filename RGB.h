//
// Created by Deanna Hartsook on 11/22/15.
//

#ifndef CS180_PROG4_RGB_H
#define CS180_PROG4_RGB_H


class RGB {
public:
    RGB(double, double, double);
    RGB(const RGB&);

    double getRed() const;
    double getGreen() const;
    double getBlue() const;

private:
    double red;
    double green;
    double blue;

};


#endif //CS180_PROG4_RGB_H
