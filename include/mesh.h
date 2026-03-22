#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "point.h"
#include "shaders.h"
#include "gl_utils.h"

class Mesh
{
protected:
    std::vector<Point> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;
    GLuint texture;

public:
    Mesh();
    virtual void Init();
    void Update();
    virtual void Render();
    void Clear();

    void SetShader(const char* vshader, const char* fshader);
    void SetTexture(const char* filename);
    void AddPoint(Point point);
    void AddFace(unsigned int index_one, unsigned int index_two, unsigned int index_three);

};
//./SB3DGS
