#include <iostream>
#include "Terrain.h"
#include "../HeaderFile/stb_image.h"

Terrain::Terrain() : vao(0), vbo(0), ibo(0), textureID(0) {}

Terrain::~Terrain() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteTextures(1, &textureID);
}

void Terrain::setup() {
    float vertices[] = {
        // pos         // texcoord
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int indices[] = { 0,1,2, 0,2,3 };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texcoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Terrain::load(const char* path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (!data) {
        std::cout << "이미지 로드 실패: " << path << std::endl;
        return;
    }

    glGenTextures(1, &textureID);   //텍스처 id 발급
    glBindTexture(GL_TEXTURE_2D, textureID);   //이 텍스처를 활성화 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //u축 반복
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   //v축 반복
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //축소시 선형보간
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //확대시 선형보간 

    //cpu메모리 -> gpu업로드 
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
   //mipmap 생성 
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
}

void Terrain::draw() {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
