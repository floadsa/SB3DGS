#include "submesh.h"

Submesh::Submesh(const Material& _material)
: material(_material)
{
	
}

void Submesh::AddIndex(unsigned int index)
{
	indices.push_back(index);
}
