#include "editbox.h"

EditBox::EditBox(int _x, int _y, int _width, int _height)
{
x = _x;
y = _y;
width = _width;
height = _height;
size = 0.05f;

Image _body(x, y , width, height);
_body.SetTexture("buttonfill.png");

Image _activebody(x, y , width, height);
_activebody.SetTexture("EditBoxActiveBody.png");

body = _body;
ActiveBody = _activebody;

text = Text(x, y + height / 10, 10, 2 ,width / 10, "~");
text.SetFont("WhiteFont.png");

}

void EditBox::UpdateSize(float _screenwidth, float _screenheight)
{

screenwidth = _screenwidth;
screenheight = _screenheight;

body.UpdateSize(screenwidth, screenheight);
ActiveBody.UpdateSize(screenwidth, screenheight);
text.UpdateSize(screenwidth, screenheight);

}

void EditBox::Update(int _mosposX, int _mosposY)
{

mosposX = _mosposX;
mosposY = _mosposY;

body.Update(_mosposX, _mosposY);
ActiveBody.Update(_mosposX, _mosposY);
text.Update(_mosposX, _mosposY);

if(!infocus)
{
	if(Get)
	text.SetText(this->Get());
}

}

void EditBox::SetSnap(bool a)
{
	snaptoright = a;
	body.SetSnap(a);
	text.SetSnap(a);
	ActiveBody.SetSnap(a);
}

void EditBox::Click()
{

if(snaptoright == true)
{
	if(infocus){Set(text.GetText());infocus = false;}
	if(mosposX > (screenwidth - x) - width && mosposY > y && mosposX < screenwidth - x && mosposY < height + y)
	{
		if(!infocus){cursore = text.GetSize();infocus = true;}
	}
}
else if(snaptoright == false)
{
	if(infocus){Set(text.GetText());infocus = false;}
	if(mosposX > x && mosposY >  y && mosposX < width + x && mosposY < height + y)
	{
		if(!infocus){cursore = text.GetSize();infocus = true;}
	}
}

}

void EditBox::Press(char lastchar, int lastkey)
{
	
	if(infocus)
	{
		if(lastkey == 259 && text.GetSize() != 0 && cursore != 0)
		{
			text.EraseLetter(cursore-1);
			cursore--;
		}
		if(lastkey == 263 && cursore != 0)
		{
			cursore--;
		}
		if(lastkey == 262 && cursore != text.GetSize())
		{
			cursore++;
		}
		else if(lastkey < 250)
		{
			text.AddLetter(lastchar, cursore);
			cursore++;
		}
	}
	
}
void EditBox::Render()
{
body.Render();

if(snaptoright == true)
{
	if(mosposX > (screenwidth - x) - width && mosposY > y && mosposX < screenwidth - x && mosposY < height + y)
	{
		ActiveBody.Render();
	}
	else if(infocus)
	{
		ActiveBody.Render();
	}
}
else if(snaptoright == false)
{
	if(mosposX > x && mosposY >  y && mosposX < width + x && mosposY < height + y)
	{
		ActiveBody.Render();
	}
	else if(infocus)
	{
		ActiveBody.Render();
	}
}

text.Render();
	
}

