#pragma once

#include <vector>
#include "image.h"
#include "text.h"
#include "button.h"
#include "UIobject.h"

class UIScene
{
protected:



public:

std::vector<UIObject*> objects;
void AddObject(UIObject* _object);
void Update(int _mosposX, int _mosposY);
void UpdateSize(float screenwidth, float screenheight);
void Check();
void Render();
	
};
