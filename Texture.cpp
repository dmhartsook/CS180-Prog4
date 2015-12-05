#include <iostream>
#include "Texture.h"

Texture::Texture(const char *filename) {
    strcpy(this->imageFile, filename);
}

void Texture::print() const {
    std::cout << "Texture file: " << this->imageFile << std::endl;
}
