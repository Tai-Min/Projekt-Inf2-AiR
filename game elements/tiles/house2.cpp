#include "house2.h"

int House2::objCount = 0;
GImage *House2::image = nullptr;
House2::House2(int x, int y)
{
    posx = x;
    posy = y;
    width = 336;
    height = 366;
    if(!objCount)
        image = new GImage("./assets/house-a.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "House2 " << objCount-1 << " created" << std::endl;
}
House2::~House2()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "House2 " << objCount << " destroyed" << std::endl;
}
bool House2::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
