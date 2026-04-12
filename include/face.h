#pragma once

#include "material.h"


class Face
{

public:

Face(unsigned int index_one, unsigned int index_two, unsigned int index_three)
{
	indices[0] = index_one;
	indices[1] = index_two;
	indices[2] = index_three;
	
};

unsigned int indices[3];
Material material;



};
