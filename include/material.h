#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Material
{
public:
std::string name;
glm::vec3 diffuse; 
glm::vec3 specular; 
float shininess; 

Material()
{diffuse = glm::vec3(0.5,0.5,0.5); name = "Standard material";}

Material(const std::string& _name)
        : name(_name) {diffuse = glm::vec3(0.5,0.5,0.5);}

	
};
