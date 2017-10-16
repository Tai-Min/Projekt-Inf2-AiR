#include "house3.h"

int House3::objCount = 0;
GImage *House3::image = nullptr;
House3::House3(int x, int y)
{
    posx = x;
    posy = y;
    width = 442;
    height = 366;
    if(!objCount)
        image = new GImage("./assets/house-c.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "House3 " << objCount-1 << " created" << std::endl;
}
House3::~House3()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "House3 " << objCount << " destroyed" << std::endl;
}
bool House3::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
