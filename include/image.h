#pragma once

#include "UImesh.h"
#include "UIobject.h"

class Image : public UIObject
{
protected:
UIMesh mesh;
int width, height, x, y;

public:

Image();
Image(int _x, int _y, int _width, int _height);
void SetTexture(const char* filename);
void SetSize(int _x, int _y, int _width, int _height);
void UpdateSize(float screenwidth, float screenheight);

float getWidth();
float getHeight();
float getX();
float getY();

void Press(char lastchar, int lastkey) override {};
void Click() override {};
void Update(int _mosposX, int _mosposY) override;
void Render() override;
	
};
