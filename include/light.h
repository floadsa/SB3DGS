#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Light
{
public:

glm::vec3 direction; 
glm::vec3 color; 


Light()
{}

Light(float x, float y, float z)
        : direction(glm::vec3(x,y,z)) {color = glm::vec3(1,1,1);}

	
};
