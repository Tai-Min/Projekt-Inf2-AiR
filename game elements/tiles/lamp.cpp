#include "lamp.h"

int Lamp::objCount = 0;
GImage *Lamp::image = nullptr;
Lamp::Lamp(int x, int y)
{
    posx = x;
    posy = y;
    width = 105;
    height = 324;
    if(!objCount)
        image = new GImage("./assets/lamp.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "Lamp " << objCount-1 << " created" << std::endl;
}
Lamp::~Lamp()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "Lamp " << objCount << " destroyed" << std::endl;
}
bool Lamp::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
