#include "button.h"

Button::Button(float _x, float _y, float _width, float _height)
{
x = _x;
y = _y;
width = _width;
height = _height;
size = 0.05f;

Image _body(x, y , width, height);
_body.SetTexture("buttonfill.png");

Image _activebody(x, y , width, height);
_activebody.SetTexture("activebuttonfill.png");

body = _body;
ActiveBody = _activebody;
text = Text(x + width / 10, y - height / 10, 10, 10, size);

text.SetFont("BFont.png");
text.SetText("Button");

}
void Button::SetText(const std::string& str)
{
	text.SetText(str);
}

void Button::SetBody(Image _body)
{
	body = _body;
}
void Button::SetActiveBody(Image _activeBody)
{
	ActiveBody = _activeBody;
}
void Button::SetText(Text _text)
{
	text = _text;
}

void Button::SetCall(std::function<void()> f)
{
	function = f;
}
void Button::Call()
{
if(function)
function();
}
void Button::Update(float _mosPosX, float _mosPosY)
{
body.Update();
text.Update();
mosPosX = _mosPosX;
mosPosY = _mosPosY;
}
void Button::Check()
{

if(mosPosX > x && mosPosY > -y && mosPosX < width + x && mosPosY < height - y)
{
	ActiveBody.Render();
	this->Call();
}

}

void Button::Render()
{
	body.Render();
	if(mosPosX > x && mosPosY > -y && mosPosX < width + x && mosPosY < height - y)
	{
	ActiveBody.Render();
	}
	text.Render();
}
