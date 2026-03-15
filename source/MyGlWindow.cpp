#define GLM_ENABLE_EXPERIMENTAL 
#define STB_IMAGE_IMPLEMENTATION

#include "MyGlWindow.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <../HeaderFile/stb_image.h>
#include <vector>

MyGlWindow::MyGlWindow(int w, int h) {
    m_width = w;
    m_height = h;

    setupBuffer();

    m_terrain = std::make_unique<Terrain>();
    m_terrain->setup();
    m_terrain->load("image/iceland_heightmap.png");
}

void MyGlWindow::setupBuffer() {
    shaderProgram = std::make_unique<ShaderProgram>();
    shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");
}

void MyGlWindow::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->use();
    m_terrain->draw();
}