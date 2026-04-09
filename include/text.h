#pragma once

#include <string>
#include "UImesh.h"
#include "UIobject.h"

class Text : public UIObject
{
protected:
UIMesh mesh;
std::string text;
std::string temptext;
float xpixelsize;
float ypixelsize;

public:
int x, y, width, height;
float size;

Text();
Text(int _x, int _y, int _width, int _height, float _size);
Text(int _x, int _y, int _width, int _height, float _size, const std::string& str);
void SetFont(const char* filename);
void SetText(const std::string& str);
void SetSize(float _x, float _y, int _width, int _height, float _size);

void Check() override {};
void Update(int _mosposX, int _mosposY) override;
void UpdateSize(float screenwidth, float screenheight) override;
void Render() override;
	
};
