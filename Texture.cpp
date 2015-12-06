#include <iostream>
#include "Texture.h"

Texture::Texture(const char *filename) {
    strcpy(this->imageFile, filename);
    this->ppm = new Ppm(filename);
}

Texture::~Texture() {
    delete this->ppm;
}

void Texture::print() const {
    std::cout << "Texture file: " << this->imageFile << std::endl;
}

Texture::Texture(const Texture &texture) {
    strcpy(this->imageFile, texture.getImageFile());
    this->ppm = new Ppm(this->imageFile);
}

const char *Texture::getImageFile() const {
    return this->imageFile;
}

const Ppm *Texture::getPpm() const {
    return this->ppm;
}
