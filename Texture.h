#ifndef CS180_PROG4_TEXTURE_H
#define CS180_PROG4_TEXTURE_H


#include "Ppm.h"

class Texture {
public:
    Texture(const char* filename);
    Texture(const Texture&);
    ~Texture();

    const char* getImageFile() const;
    const Ppm* getPpm() const;

    void print() const;

private:
    char imageFile[50];
    Ppm* ppm;
};


#endif //CS180_PROG4_TEXTURE_H
