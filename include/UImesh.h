#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include "gl_utils.h"
#include "mesh.h"

class UIMesh
{

protected:

std::vector<Point> vertices;
std::vector<unsigned int> indices;
GLuint VAO, VBO, EBO;
GLuint shaderProgram;
GLuint texture;

public:

UIMesh();
void Init();
void Update();
void Render();
void SetTexture(const char* filename);
void Clear();
void AddPoint(Point point);
void AddFace(unsigned int index_one, unsigned int index_two, unsigned int index_three);





};
