#pragma once

#include <vector>
#include <string>
#include "image.h"
#include "text.h"
#include "button.h"
#include "editbox.h"
#include "UIobject.h"

class UIScene
{
protected:

public:
char lastchar;
unsigned int lastkey;
bool anykeypressed = false;

std::vector<UIObject*> objects;
void AddObject(UIObject* _object);
void Update(int _mosposX, int _mosposY);
void UpdateSize(float screenwidth, float screenheight);
void Click();
void Press();
void Render();
	
};
