#pragma once

#include <vector> 
#include "material.h" 

class Submesh
{
public:
	std::vector<unsigned int> indices;
	Material material;

	Submesh(const Material& _material);

	void AddIndex(unsigned int index);

};
