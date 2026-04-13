#pragma once

#include <functional>
#include "image.h"
#include "text.h"
#include "UIobject.h"

class EditBox : public UIObject
{
protected:

Image body;
Image ActiveBody;
Text text;

bool infocus = false;
int x, y, width, height, size;
int mosposX, mosposY;
float screenwidth, screenheight; 

int cursore = 0;

std::function<std::string()> Get;
std::function<void(const std::string&)> Set;

public:

float* test;

void SetGetFunc(std::function<std::string()> _function){Get = _function;}
void SetSetFunc(std::function<void(const std::string&)> _function){Set = _function;}

EditBox(int _x, int _y, int _width, int _height);
void UpdateSize(float width, float height);
void SetSnap(bool a) override;
void Click() override;
void Press(char lastchar, int lastkey) override;
void Update(int _mosposX, int _mosposY)override;
void Render()override;

	
};
