#include "well.h"

int Well::objCount = 0;
GImage *Well::image = nullptr;
Well::Well(int x, int y)
{
    posx = x;
    posy = y;
    width = 130;
    height = 130;
    if(!objCount)
        image = new GImage("./assets/well.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "Well " << objCount-1 << " created" << std::endl;
}
Well::~Well()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "Well " << objCount << " destroyed" << std::endl;
}
bool Well::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
