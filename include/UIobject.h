#pragma once
#include <iostream>


class UIObject
{
public:
bool activity = true;
protected:
bool snaptoright = false;

public:
virtual void SetSnap(bool a) {snaptoright = a;};
virtual void Render() = 0;
virtual void Update(int _mosposX, int _mosposY) = 0;
virtual void UpdateSize(float screenwidth, float screenheight) = 0;
virtual void Check() = 0;

};
