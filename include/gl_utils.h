#pragma once

#include <glad/glad.h>

GLuint CompileShader(GLenum type, const char* source);
GLuint CreateShaderProgram(const char* vshader, const char* fshader);
GLuint CreateTexture(const char* filename);


