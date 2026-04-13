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
void AddLetter(const char& letter, unsigned int cursore);
void EraseLetter(unsigned int cursore);
void SetSize(float _x, float _y, int _width, int _height, float _size);

size_t GetSize();
std::string GetText();
void Press(char lastchar, int lastkey) override {};
void Click() override {};
void Update(int _mosposX, int _mosposY) override;
void UpdateSize(float screenwidth, float screenheight) override;
void Render() override;
	
};
