#include "object.h"
#include "light.h"
//#include "iostream"

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
	glBufferData(GL_ARRAY_BUFFER, 200000 * sizeof(Point), nullptr, GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 200000 * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(offsetof(Point, u)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(offsetof(Point, nx)));
	glEnableVertexAttribArray(2);
}

void Object::Update(int i)
{
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Point), vertices.data());
	
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

glBindVertexArray(0);
}


void Object::Render(glm::mat4 view, glm::mat4 proj, Camera camera)
{

//Later i will develop normal light

glm::vec3 lightDirs[16];
glm::vec3 lightColors[16];

for (int i = 0; i < 16; ++i) 
{
    lightDirs[i] = camera.position;
    lightColors[i] = glm::vec3(1,1,1);
}

for(int i = 0; i < submeshes.size(); i++)
{

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Point), vertices.data());
	
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, submeshes[i].indices.size() * sizeof(unsigned int), submeshes[i].indices.data());

glBindVertexArray(0);

// Updating above

glUseProgram(shaderProgram);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);

glUniform3fv(glGetUniformLocation(shaderProgram, "lightDir"), 2, &lightDirs[0][0]);
glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 2, &lightColors[0][0]);


glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), camera.position.x, camera.position.y, camera.position.z);


glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
glUniform4f(glGetUniformLocation(shaderProgram, "diffuse"), submeshes[i].material.diffuse.x, submeshes[i].material.diffuse.y, submeshes[i].material.diffuse.z, 1);
glUniform3f(glGetUniformLocation(shaderProgram, "specular"), submeshes[i].material.specular.x, submeshes[i].material.specular.y, submeshes[i].material.specular.z);
glUniform1f(glGetUniformLocation(shaderProgram, "shininess"), submeshes[i].material.shininess);

GLint projLoc = glGetUniformLocation(shaderProgram, "proj");
GLint viewLoc = glGetUniformLocation(shaderProgram, "view");

glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, submeshes[i].indices.size(), GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
}
}
void Object::AddMaterial()
{
	materials.push_back(Material());
}
void Object::AddSubmesh(Material material)
{
	submeshes.push_back(Submesh(material));
}

void Object::SetTexture(const char* filename)
{
texture = CreateTexture(filename);
}

void Object::Dump()
{

	for(int i = 0; i < vertices.size(); i++)
	{
	std::cout << " Number: " << i << std::endl;
	std::cout << " X: " << vertices[i].x << " Y: " << vertices[i].y << " Z: " << vertices[i].z << std::endl;
	std::cout << " U: " << vertices[i].u << " V: " << vertices[i].v << std::endl;
	std::cout << " NX: " << vertices[i].nx << " NY: " << vertices[i].ny << " NZ: " << vertices[i].nz << std::endl << std::endl;
	}
	std::cout << std::endl;
	
	std::cout << "- - - - - - - - Indices: - - - - - - - -" << std::endl;
	for(int i = 0; i < indices.size(); i+=3)
	{
	std::cout << "| " << indices[i] << " | "  << indices[i+1] << " | "  << indices[i+2] << " |" << std::endl;
	}
	std::cout << "- - - - - - - - - - - - -  - - - - - - - -" << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < submeshes.size(); i++)
	{
	std::cout << std::endl;
	std::cout << "Material: " << submeshes[i].material.name << std::endl;
	std::cout << "Diffuse: " << "R: " <<submeshes[i].material.diffuse.x << " G: " <<submeshes[i].material.diffuse.y << " B: " <<submeshes[i].material.diffuse.z << std::endl;
	std::cout << "Specular: " << "R: " <<submeshes[i].material.specular.x << " Y: " <<submeshes[i].material.specular.y << " Z: " <<submeshes[i].material.specular.z << std::endl;
	std::cout << "Shininess: " <<submeshes[i].material.shininess << std::endl;
	}

	std::cout << std::endl << " Amount of vertices: " << vertices.size() << std::endl;
	
}


void Object::ReNormal()
{
	for(int i = 0; i < indices.size(); i+=3)
	{
		glm::vec3 a = glm::vec3(vertices[indices[i+1]].x, vertices[indices[i+1]].y, vertices[indices[i+1]].z) - glm::vec3(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
		glm::vec3 b = glm::vec3(vertices[indices[i+2]].x, vertices[indices[i+2]].y, vertices[indices[i+2]].z) - glm::vec3(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);

		glm::vec3 n = glm::normalize(glm::cross(a, b));

		vertices[indices[i]].nx = n.x;
		vertices[indices[i]].ny = n.y;
		vertices[indices[i]].nz = n.z;

		vertices[indices[i+1]].nx = n.x;
		vertices[indices[i+1]].ny = n.y;
		vertices[indices[i+1]].nz = n.z;

		vertices[indices[i+2]].nx = n.x;
		vertices[indices[i+2]].ny = n.y;
		vertices[indices[i+2]].nz = n.z;
	}
	//std::cout << vertices.size() << std::endl;
}


