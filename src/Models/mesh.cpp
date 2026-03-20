#include "mesh.h"


Mesh::Mesh()
{
	
}

void Mesh::Init()
{
shaderProgram = CreateShaderProgram(CmnVxShader, CmnFgShader);	

glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(Point), nullptr, GL_DYNAMIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000 * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(offsetof(Point, u)));
glEnableVertexAttribArray(1);
}

void Mesh::Update()
{
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Point), vertices.data());
	
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

glBindVertexArray(0);
}

void Mesh::Render()
{
glUseProgram(shaderProgram);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);

glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
}

void Mesh::SetShader(const char* vshader, const char* fshader)
{
shaderProgram = CreateShaderProgram(CmnVxShader, CmnFgShader);	
}

void Mesh::SetTexture(const char* filename)
{
texture = CreateTexture(filename);
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
