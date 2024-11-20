// Texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GLFW/glfw3.h>

class Texture {
public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind() const;
    void unbind() const;

private:
    GLuint textureID;
    void loadTexture(const std::string& filePath);
};

#endif // TEXTURE_H
