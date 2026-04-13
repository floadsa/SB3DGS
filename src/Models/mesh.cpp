#include "mesh.h"


Mesh::Mesh()
{
	
}

void Mesh::SetShader(const char* vshader, const char* fshader)
{
	shaderProgram = CreateShaderProgram(vshader, fshader);	
}

void Mesh::AddPoint(glm::vec3 point)
{points.push_back(point);}

void Mesh::AddVertex(Vertex vertex){vertices.push_back(vertex);}

void Mesh::AddMaterial(Material _material)
{
	materials.push_back(_material);
}

void Mesh::AddFace(unsigned int index_one, unsigned int index_two, unsigned int index_three)
{

}
