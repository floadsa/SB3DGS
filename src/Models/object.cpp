#include "object.h"
#include "light.h"

Object::Object()
{

}
void Object::Init()
{

pivot = glm::vec3(0,0,0);

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

void Object::Update()
{

}

void Object::SetPosition(float _x, float _y, float _z)
{
glm::vec3 move_value = glm::vec3(_x, _y, _z) - pivot;

pivot = glm::vec3(_x, _y, _z);

for(int i = 0; i < points.size(); i++)
{
	points[i] += move_value;	
}
dirtmesh = true;
}


void Object::Render(glm::mat4 view, glm::mat4 proj, Camera camera)
{

//Later i will develop normal light
std::vector<Point> rpoint;

glm::vec3 lightDirs[2];
glm::vec3 lightColors[2];

lightDirs[0] = camera.position;
lightDirs[1] = -camera.position;

for (int i = 0; i < 2; ++i) 
{
  lightColors[i] = glm::vec3(1,1,1);
}

if(dirtmesh)
{
	for(int i = 0; i < materials.size(); i++)
	{
		submeshes.push_back(Submesh(materials[i]));
		for(int j = 0; j < faces.size(); j++)
		{
		if(faces[j].material.name != submeshes.back().material.name){continue;}
		submeshes.back().AddFace(faces[j]);
		}
	}


	for(int i = 0; i < vertices.size(); i++)
	{
			rpoint.push_back
			(
   			Point(
        	points[vertices[i].position_index].x,
        	points[vertices[i].position_index].y,
        	points[vertices[i].position_index].z,
        	vertices[i].u,
        	vertices[i].v,
        	vertices[i].nx,
        	vertices[i].ny,
        	vertices[i].nz
    		)
		);
	}

	dirtmesh = false;
}


for(int i = 0; i < submeshes.size(); i++)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, rpoint.size() * sizeof(Point), rpoint.data());
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, submeshes[i].indices.size() * sizeof(unsigned int), submeshes[i].indices.data());

	glBindVertexArray(0);

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

void Object::SetTexture(const char* filename)
{
	texture = CreateTexture(filename);
}

void Object::Dump()
{

//THIS FOR DEBUGING
/*
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



	std::cout << std::endl;
	for(int i =0; i < submeshes.size(); i++)
	{
	std::cout << submeshes[i].indices.size() << std::endl;
	}

	for(int i = 0; i < materials.size(); i++)
	{
	std::cout << std::endl;
	std::cout << "Material: " << materials[i].name << std::endl;
	std::cout << "Diffuse: " << "R: " <<materials[i].diffuse.x << " G: " <<materials[i].diffuse.y << " B: " <<materials[i].diffuse.z << std::endl;
	std::cout << "Specular: " << "R: " <<materials[i].specular.x << " Y: " <<materials[i].specular.y << " Z: " <<materials[i].specular.z << std::endl;
	std::cout << "Shininess: " <<materials[i].shininess << std::endl;
	}

			for(int i = 0; i < submeshes.size(); i++)
			{
			std::cout << std::endl;
			std::cout << "Material: " << submeshes[i].material.name << std::endl;
			std::cout << "Indices: " << submeshes[i].indices.size() << std::endl;
			std::cout << "Diffuse: " << "R: " <<submeshes[i].material.diffuse.x << " G: " <<submeshes[i].material.diffuse.y << " B: " <<submeshes[i].material.diffuse.z << std::endl;
			std::cout << "Specular: " << "R: " <<submeshes[i].material.specular.x << " Y: " <<submeshes[i].material.specular.y << " Z: " <<submeshes[i].material.specular.z << std::endl;
			std::cout << "Shininess: " <<submeshes[i].material.shininess << std::endl;
			}
			std::cout << std::endl << " Amount of vertices: " << vertices.size() << std::endl;
			
	for(int i = 0; i < materials.size(); i++)
	{
	std::cout << std::endl;
	std::cout << "Material: " << materials[i].name << std::endl;
	std::cout << "Diffuse: " << "R: " <<materials[i].diffuse.x << " G: " <<materials[i].diffuse.y << " B: " <<materials[i].diffuse.z << std::endl;
	std::cout << "Specular: " << "R: " <<materials[i].specular.x << " Y: " <<materials[i].specular.y << " Z: " <<materials[i].specular.z << std::endl;
	std::cout << "Shininess: " <<materials[i].shininess << std::endl;
	} */
	
	

	/*	for(int i = 0; i < faces.size(); i++)
		{
			std::cout << std::endl;
			std::cout << faces[i].indices[0] << " "<< faces[i].indices[1] <<" "<< faces[i].indices[2] <<std::endl;
			std::cout << faces[i].material->name << " " << faces[i].material->diffuse.x << faces[i].material->diffuse.y << std::endl;
		}*/
/*
		for(int i = 0; i < vertices.size(); i++)
		{
		std::cout << " Number: " << i << std::endl;
		std::cout << " X: " << vertices[i].x << " Y: " << vertices[i].y << " Z: " << vertices[i].z << std::endl;
		std::cout << " U: " << vertices[i].u << " V: " << vertices[i].v << std::endl;
		std::cout << " NX: " << vertices[i].nx << " NY: " << vertices[i].ny << " NZ: " << vertices[i].nz << std::endl << std::endl;
		}
		std::cout << std::endl;*/
		
	//	std::cout << "- - - - - - - - Indices: - - - - - - - -" << std::endl;
	//	for(int i = 0; i < indices.size(); i+=3)
	//	{
	//	std::cout << "| " << indices[i] << " | "  << indices[i+1] << " | "  << indices[i+2] << " |" << std::endl;
	//	}
	//	std::cout << "- - - - - - - - - - - - -  - - - - - - - -" << std::endl;
	//	std::cout << std::endl;
/*
for(int i = 0; i < points.size(); i++)
{
std::cout << " POINT: " << i << " " << points[i].x << " " << points[i].y << " " << points[i].z << std::endl;
}

for(int i = 0; i < vertices.size(); i++)
{
std::cout << " VERTEX: " << i << " " << vertices[i].position_index << std::endl;
}
*/
}


void Object::ReNormal()
{
	//DOES NOT WORK WELL
	for(int i = 0; i < faces.size(); i++)
	{
		glm::vec3 a = points[vertices[faces[i].indices[0]].position_index] -
					  points[vertices[faces[i].indices[1]].position_index];

		glm::vec3 b = points[vertices[faces[i].indices[0]].position_index] -
					  points[vertices[faces[i].indices[2]].position_index];

		glm::vec3 n = glm::normalize(glm::cross(a, b));

		vertices[faces[i].indices[0]].nx = n.x;
		vertices[faces[i].indices[0]].ny = n.y;
		vertices[faces[i].indices[0]].nz = n.z;

		vertices[faces[i].indices[1]].nx = n.x;
		vertices[faces[i].indices[1]].ny = n.y;
		vertices[faces[i].indices[1]].nz = n.z;

		vertices[faces[i].indices[2]].nx = n.x;
		vertices[faces[i].indices[2]].ny = n.y;
		vertices[faces[i].indices[2]].nz = n.z;
	}
}


