#include "house1.h"

int House1::objCount = 0;
GImage *House1::image = nullptr;
House1::House1(int x, int y)
{
    posx = x;
    posy = y;
    width = 420;
    height = 488;
    if(!objCount)
        image = new GImage("./assets/house-b.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "House1 " << objCount-1 << " created" << std::endl;
}
House1::~House1()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "House1 " << objCount << " destroyed" << std::endl;
}
bool House1::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
