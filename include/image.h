#pragma once

#include "object.h"

class Image
{
protected:
    Object mesh;
    float width;
    float height;
    float x;
    float y;

    public:

    Image();
    Image(float _x, float _y, float _width, float _height);
    void SetTexture(const char* filename);
    void SetSize(float _x, float _y, float _width, float _height);

    float getWidth();
    float getHeight();
    float getX();
    float getY();

    void Update();
    void Render(const glm::mat4& projview);
	
};
