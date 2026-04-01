#include "UImesh.h"

UIMesh::UIMesh()
{
	
}
void UIMesh::Init()
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

void UIMesh::Update()
{
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Point), vertices.data());
	
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

glBindVertexArray(0);
}

void UIMesh::Render()
{
	glUseProgram(shaderProgram);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void UIMesh::SetTexture(const char* filename)
{
texture = CreateTexture(filename);
}
