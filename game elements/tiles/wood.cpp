#include "wood.h"

int Wood::objCount = 0;
GImage *Wood::image = nullptr;
Wood::Wood(int x, int y)
{
    posx = x;
    posy = y;
    width = 96;
    height = 32;
    if(!objCount)
        image = new GImage("./assets/tiles/wood.jpg",width,height,GImage::IS_SOLID,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "Wood " << objCount-1 << " created" << std::endl;
}
Wood::~Wood()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "Wood " << objCount << " destroyed" << std::endl;
}
bool Wood::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;

}
