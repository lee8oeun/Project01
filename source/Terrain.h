#pragma once
#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Shader.h"

class Terrain {
public:
    Terrain();
    ~Terrain();
    void load(const char* path);
    void setup();
    void draw(); //하라라

private:
    GLuint vao, vbo, ibo, textureID;
};