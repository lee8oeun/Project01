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
    void draw();

private:
    GLuint vao, vbo, ibo, textureID;
};