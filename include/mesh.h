#pragma once

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "point.h"
#include "shaders.h"
#include "gl_utils.h"
#include "face.h"
#include "vertex.h"

class Mesh
{
protected:

std::vector<Vertex> vertices;
GLuint VAO, VBO, EBO;
GLuint shaderProgram;

public:

std::vector<glm::vec3> points;
std::vector<Material> materials;
std::vector<Face> faces;

Mesh();

void AddMaterial(Material _material);
void SetShader(const char* vshader, const char* fshader);
void SetTexture(const char* filename);
void AddPoint(glm::vec3 point);
void AddVertex(Vertex vertex);
void AddFace(unsigned int index_one, unsigned int index_two, unsigned int index_three);


};
//./SB3DGS
