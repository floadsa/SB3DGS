#include "text.h"

Text::Text()
{
mesh.Init();
}

Text::Text(int _x, int _y, int _width, int _height, float _size)
{
x = _x;
y = _y;
width = _width;
height = _height;
size = _size;
this->SetText("text");
mesh.SetTexture("WhiteFont.png");
mesh.Init();
}

Text::Text(int _x, int _y, int _width, int _height, float _size, const std::string& str)
{
x = _x;
y = _y;
width = _width;
height = _height;
text = str;
size = _size;
mesh.SetTexture("WhiteFont.png");
mesh.Init();
}

void Text::SetFont(const char* filename)
{
mesh.SetTexture(filename);
}
void Text::SetText(const std::string& str)
{
text = str;	
}
std::string Text::GetText()
{
return text;
}

void Text::SetSize(float _x, float _y, int _width, int _height, float _size)
{
size = _size;
width = _width;
height = _height;
x = _x;
y = _y;
}

size_t Text::GetSize()
{
return text.size();
}

void Text::AddLetter(const char& letter, unsigned int cursore)
{
	text.insert(cursore, 1, letter);
}
void Text::EraseLetter(unsigned int cursore)
{
	text.erase(cursore, 1);
}

void Text::UpdateSize(float screenwidth, float screenheight)
{
	mesh.Clear();
	
	float realwidth, realheight;
	float realx, realy;
	xpixelsize = 2.0f / screenwidth;
	ypixelsize = 2.0f / screenheight;
	
	realwidth = size * xpixelsize;
	realheight = size * ypixelsize;
	realy = 1 - (y * ypixelsize);

	if(snaptoright == true)
	{
	realx = 1 - ((x * xpixelsize)) - width * realwidth;
	
	}
	else if(snaptoright == false)
	{
	realx = (x * xpixelsize) - 1;
	}

	for (size_t i = 0; i < text.size(); ++i)
	{
	char c = text[i];
	unsigned char ascii = (unsigned char)c;
	
	int col = ascii % 16;
	int row = ascii / 16;
	int base = i * 4;
	
	int rowl = i / width;
	if(height <= rowl){break;}
	
	int coll = i % width;
	
	float xpos = realx + coll * realwidth;
	float ypos = realy - rowl * realheight; 
	
	float step = 1.0f/16.0f;
	
	mesh.AddPoint(Point(xpos            , ypos,             0, step * col 	     , 1 - (step * row)));
	mesh.AddPoint(Point(xpos + realwidth, ypos,             0, step * col + step , 1 - (step * row)));
	mesh.AddPoint(Point(xpos            , ypos - realheight,0, step * col	     , 1 - (step * row + step)));
	mesh.AddPoint(Point(xpos + realwidth, ypos - realheight,0, step * col + step , 1 - (step * row + step)));
	
	mesh.AddFace(base + 0, base + 1, base + 2);
	mesh.AddFace(base + 1, base + 3, base + 2);
	
	}

	mesh.Update();
}

void Text::Update(int _mosposX, int _mosposY)
{


	if(temptext != text)
	{
	
	mesh.Clear();
	float realwidth, realheight;
	float realx, realy;
	
	realwidth = size * xpixelsize;
	realheight = size * ypixelsize;
	realy = 1 - (y * ypixelsize);

	if(snaptoright == true)
	{
	realx = 1 - ((x * xpixelsize)) - width * realwidth;
	}
	else if(snaptoright == false)
	{
	realx = (x * xpixelsize) - 1;
	}

	for (size_t i = 0; i < text.size(); ++i)
	{
	char c = text[i];
	unsigned char ascii = (unsigned char)c;
	
	int col = ascii % 16;
	int row = ascii / 16;
	int base = i * 4;
	
	int rowl = i / width;
	if(height <= rowl){break;}
	
	int coll = i % width;
	
	float xpos = realx + coll * realwidth;
	float ypos = realy - rowl * realheight; 
	
	float step = 1.0f/16.0f;
	
	mesh.AddPoint(Point(xpos            , ypos,             0, step * col 	     , 1 - (step * row)));
	mesh.AddPoint(Point(xpos + realwidth, ypos,             0, step * col + step , 1 - (step * row)));
	mesh.AddPoint(Point(xpos            , ypos - realheight,0, step * col	     , 1 - (step * row + step)));
	mesh.AddPoint(Point(xpos + realwidth, ypos - realheight,0, step * col + step , 1 - (step * row + step)));
	
	mesh.AddFace(base + 0, base + 1, base + 2);
	mesh.AddFace(base + 1, base + 3, base + 2);
	}
	temptext = text;
	mesh.Update();
	}

}

void Text::Render()
{
mesh.Render();
}
