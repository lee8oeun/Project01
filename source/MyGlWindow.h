//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include <memory>
#include "Shader.h"
#include "Terrain.h"

class MyGlWindow {
public:
    MyGlWindow(int w, int h);
    void draw();

private:
    int m_width, m_height;
    std::unique_ptr<ShaderProgram> shaderProgram;
    std::unique_ptr<Terrain> m_terrain;

    void setupBuffer();
};
