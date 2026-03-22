#include "object.h"
#include "iostream"

Object::Object()
{

}
void Object::Init()
{

	shaderProgram = CreateShaderProgram(VlmVxShader, VlmFgShader);	
	
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

void Object::Render(const glm::mat4 &view, const glm::mat4 &proj)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

	GLint projLoc  = glGetUniformLocation(shaderProgram, "proj");
	GLint viewLoc  = glGetUniformLocation(shaderProgram, "view");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Object::Render(const glm::mat4 &projview)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

	GLint projLoc  = glGetUniformLocation(shaderProgram, "proj");
	GLint viewLoc  = glGetUniformLocation(shaderProgram, "view");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projview));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
