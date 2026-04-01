#include "mesh.h"


Mesh::Mesh()
{
	
}

void Mesh::SetShader(const char* vshader, const char* fshader)
{
shaderProgram = CreateShaderProgram(CmnVxShader, CmnFgShader);	
}


void Mesh::Clear()
{
	vertices.clear();
	indices.clear();
}


void Mesh::AddPoint(Point point)
{vertices.push_back(point);}

void Mesh::AddFace(unsigned int index_one, unsigned int index_two, unsigned int index_three)
{
indices.push_back(index_one);
indices.push_back(index_two);
indices.push_back(index_three);
}
void Mesh::AddIndex(unsigned int index)
{
indices.push_back(index);
}
