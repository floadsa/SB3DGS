#pragma once
#include "mesh.h"
#include "shaders.h"
#include "gl_utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object : public Mesh
{
protected:

public:
    Object();

    void Init() override;

    void Render(const glm::mat4 &view, const glm::mat4 &proj);
    void Render(const glm::mat4 &projview); // For Ortho
};
