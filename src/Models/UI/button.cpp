#include "button.h"

Button::Button(float _nx, float _ny, float _nwidth, float _nheight)
{
	nx = _nx;
	ny = _ny;
	nwidth = _nwidth;
	nheight = _nheight;
	size = 0.05f;

	Image _body(nx, ny, nwidth, nheight);
	_body.SetTexture("buttonfill.png");

	Image _activebody(nx - 0.01f, ny - 0.01f, nwidth + 0.01f, nheight + 0.01f);
	_activebody.SetTexture("activebuttonfill.png");

	body = _body;
	ActiveBody = _activebody;
	text = Text(nx + nwidth / 2.0f, ny + nheight / 2.0f, 10, 10, size);

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

void Button::Update()
{
	body.Update();
	text.Update();
}

void Button::Check(float mosPosX, float mosPosY, const glm::mat4& projview)
{
	if(mosPosX > nx && mosPosY > ny && mosPosX < nwidth + nx && mosPosY < nheight + ny)
	{
		ActiveBody.Render(projview);
		this->Call();
	}
}

void Button::Render(float mosPosX, float mosPosY, const glm::mat4& projview)
{
	body.Render(projview);
	if(mosPosX > nx && mosPosY > -ny && mosPosX < nwidth + nx && mosPosY < nheight - ny)
	{
		ActiveBody.Render(projview);
	}
	text.Render(projview);
}
