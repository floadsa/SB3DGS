#pragma once

#include <functional>
#include "image.h"
#include "text.h"
#include "UIobject.h"

class Button : public UIObject
{
protected:

std::function<void()> function;
Image body;
Image ActiveBody;
Text text;

int x, y, width, height, size;
int mosposX, mosposY;
float screenwidth, screenheight;

public:

Button(int _x, int _y, int _width, int _height);

void Call();
void SetText(const std::string& str);
void UpdateSize(float width, float height);
void SetCall(std::function<void()> _function);

void SetSnap(bool a) override;

void Press(char lastchar, int lastkey) override {};
void Click() override;
void Update(int _mosposX, int _mosposY)override;
void Render()override;

	
};
