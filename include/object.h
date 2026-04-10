#pragma once
#include "mesh.h"
#include "camera.h"
#include "shaders.h"
#include "gl_utils.h"
#include "submesh.h"
#include "material.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object : public Mesh
{
protected:

public:
GLuint texture;
std::vector<Submesh> submeshes;
std::vector<Material> materials;

Object();
void Init();
void Update(int i);
void Render(glm::mat4 view, glm::mat4 prog, Camera camera);
void ReNormal();
void AddMaterial();
void SetTexture(const char* filename);
void AddSubmesh(Material material);

void Dump();



};
