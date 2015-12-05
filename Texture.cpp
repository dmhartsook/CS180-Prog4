#include <iostream>
#include "Texture.h"

Texture::Texture(const char *filename) {
    strcpy(this->imageFile, filename);
}

void Texture::print() const {
    std::cout << "Texture file: " << this->imageFile << std::endl;
}

Texture::Texture(const Texture &texture) {
    strcpy(this->imageFile, texture.getImageFile());
}

const char *Texture::getImageFile() const {
    return this->imageFile;
}
