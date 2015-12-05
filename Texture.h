#ifndef CS180_PROG4_TEXTURE_H
#define CS180_PROG4_TEXTURE_H


class Texture {
public:
    Texture(const char* filename);

    void print() const;

private:
    char imageFile[50];
};


#endif //CS180_PROG4_TEXTURE_H
