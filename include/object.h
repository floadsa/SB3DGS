#pragma once
#include "mesh.h"
#include "camera.h"
#include "shaders.h"
#include "gl_utils.h"
#include "submesh.h"
#include "material.h"
#include "face.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object : public Mesh
{
protected:
std::vector<Submesh> submeshes;
public:
bool dirtmesh = true;
GLuint texture;
//std::vector<Material> materials;
//std::vector<Face> faces;

Object();
void Init();
void Update();
void Render(glm::mat4 view, glm::mat4 prog, Camera camera);
void ReNormal();
void SetTexture(const char* filename);

void Dump();



};
