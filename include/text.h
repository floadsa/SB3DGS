#pragma once

#include <string>
#include "object.h"

class Text
{
protected:
    Object mesh;
    std::string text;

    public:
    float x, y, size;
    int width, height;

    Text();
    Text(float _x, float _y, int _width, int _height, float _size);
    void SetFont(const char* filename);
    void SetText(const std::string& str);
    void SetSize(float _x, float _y, int _width, int _height, float _size);
    void Update();
    void Render(const glm::mat4& projview);
	
};
