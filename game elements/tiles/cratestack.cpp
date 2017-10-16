#include "cratestack.h"

int CrateStack::objCount = 0;
GImage *CrateStack::image = nullptr;
CrateStack::CrateStack(int x, int y)
{
    posx = x;
    posy = y;
    width = 146;
    height = 136;
    if(!objCount)
        image = new GImage("./assets/crate-stack.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "CrateStack " << objCount-1 << " created" << std::endl;
}
CrateStack::~CrateStack()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "CrateStack " << objCount << " destroyed" << std::endl;
}
bool CrateStack::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
