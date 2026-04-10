#include "image.h"

Image::Image()
{
mesh.Init();
}

Image::Image(int _x, int _y, int _width, int _height)
{
width = _width;
height = _height;
x = _x;
y = _y;

mesh.Init();

this->SetTexture("buttonfill.png");


}

void Image::SetSize(int _x, int _y, int _width, int _height)
{

}

void Image::UpdateSize(float screenwidth, float screenheight)
{
mesh.Clear();

float realwidth, realheight;
float realx, realy;
float xpixelsize = 2.0f / screenwidth;
float ypixelsize = 2.0f / screenheight;

realwidth = width * xpixelsize;
realheight = height * ypixelsize;
realy = 1 - (y * ypixelsize);

if(snaptoright == true)
{
realx = 1 - ((x * xpixelsize)) - realwidth;
}
else if(snaptoright == false)
{
realx = (x * xpixelsize) - 1;
}

mesh.AddPoint(Point(realx            ,realy             ,0,1,1));
mesh.AddPoint(Point(realx + realwidth,realy             ,0,0,1));
mesh.AddPoint(Point(realx            ,realy - realheight,0,1,0));
mesh.AddPoint(Point(realx + realwidth,realy - realheight,0,0,0));
mesh.AddFace(2,0,1);
mesh.AddFace(1,2,3);
mesh.Update();

}

float Image::getWidth() { return width; }
float Image::getHeight() { return height; }
float Image::getX() { return x; }
float Image::getY() { return y; }

void Image::SetTexture(const char* filename)
{
mesh.SetTexture(filename);
}
void Image::Update(int mosposX, int _mosposY)
{
mesh.Update();
}
void Image::Render()
{
mesh.Render();
}
