#include "submesh.h"

Submesh::Submesh(Material _material)
{
	material = _material;
}

void Submesh::AddFace(Face _face)
{
	indices.push_back(_face.indices[0]);
	indices.push_back(_face.indices[1]);
	indices.push_back(_face.indices[2]);
}
