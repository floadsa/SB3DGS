#pragma once

#include <vector> 
#include "material.h" 
#include "face.h" 

class Submesh
{
public:
	std::vector<unsigned int> indices;
	Material material;

	Submesh(Material _material);

	void AddFace(Face _face);
	

};
