#include "UIscene.h"


void UIScene::AddObject(UIObject* _object)
{
	objects.push_back(_object);
}
void UIScene::Render()
{
	for(int i = 0; i < objects.size(); i++)
	objects[i]->Render();
}
void UIScene::Update(int _mosposX, int _mosposY)
{
	for(int i = 0; i < objects.size(); i++)
	objects[i]->Update(_mosposX, _mosposY);
}
void UIScene::UpdateSize(float screenwidth, float screenheight)
{
	for(int i = 0; i < objects.size(); i++)
	objects[i]->UpdateSize(screenwidth, screenheight);
}
void UIScene::Check()
{
	for(int i = 0; i < objects.size(); i++)
	objects[i]->Check();
}

