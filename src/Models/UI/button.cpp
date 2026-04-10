#include "button.h"

Button::Button(int _x, int _y, int _width, int _height)
{
x = _x;
y = _y;
width = _width;
height = _height;
size = 0.05f;

Image _body(x, y , width, height);
_body.SetTexture("buttonfill.png");

Image _activebody(x, y , width, height);
_activebody.SetTexture("outline.png");

body = _body;
ActiveBody = _activebody;


text = Text(x, y + height /10, 10, 2 ,width / 10, "Button");
text.SetFont("WhiteFont.png");

}
void Button::SetText(const std::string& str)
{
	text.SetText(str);
}
void Button::UpdateSize(float _screenwidth, float _screenheight)
{
screenwidth = _screenwidth;
screenheight = _screenheight;

body.UpdateSize(screenwidth, screenheight);
ActiveBody.UpdateSize(screenwidth, screenheight);
text.UpdateSize(screenwidth, screenheight);

}

void Button::SetCall(std::function<void()> _function)
{
function = _function;
}
void Button::Call()
{
if(function)
function();
}
void Button::Update(int _mosposX, int _mosposY)
{
mosposX = _mosposX;
mosposY = _mosposY;

body.Update(_mosposX, _mosposY);
ActiveBody.Update(_mosposX, _mosposY);
text.Update(_mosposX, _mosposY);
}

void Button::SetSnap(bool a)
{
	snaptoright = a;
	body.SetSnap(a);
	text.SetSnap(a);
	ActiveBody.SetSnap(a);
}

void Button::Check()
{

if(snaptoright == true)
{
if(mosposX > (screenwidth - x) - width && mosposY > y && mosposX < screenwidth - x && mosposY < height + y)
{this->Call();}
}
else if(snaptoright == false)
{
if(mosposX > x && mosposY >  y && mosposX < width + x && mosposY < height + y)
{this->Call();}
}

}

void Button::Render()
{
	body.Render();
	text.Render();

	if(snaptoright == true)
	{
	if(mosposX > (screenwidth - x) - width && mosposY > y && mosposX < screenwidth - x && mosposY < height + y)
	{ActiveBody.Render();}
	}
	else if(snaptoright == false)
	{
	if(mosposX > x && mosposY >  y && mosposX < width + x && mosposY < height + y)
	{
	ActiveBody.Render();}
	}
	
	
}

