#pragma once

#include "object.h"
#include "camera.h"
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

class Scene
{
protected:

int CurrentCamera;

public:

std::vector<Object> objects;
std::vector<Camera> cameras;

Scene();
void Update();
void AddObject();
void ConvertFromObj(const char* objfilename);
void Render();
	
};
