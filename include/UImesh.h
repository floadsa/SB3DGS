#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include "gl_utils.h"
#include "mesh.h"

class UIMesh : public Mesh
{

protected:

GLuint texture;

public:

UIMesh();
void Init();
void Update();
void Render();
void SetTexture(const char* filename);




};
