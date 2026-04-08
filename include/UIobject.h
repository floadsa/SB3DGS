#pragma once
#include <iostream>


class UIObject
{
protected:

public:
virtual void Render() = 0;
virtual void Update(int _mosposX, int _mosposY) = 0;
virtual void UpdateSize(float screenwidth, float screenheight) = 0;
virtual void Check() = 0;

};
