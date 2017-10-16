#include "crate.h"

int Crate::objCount = 0;
GImage *Crate::image = nullptr;
Crate::Crate(int x, int y)
{
    posx = x;
    posy = y;
    width = 78;
    height = 70;
    if(!objCount)
        image = new GImage("./assets/crate.gif",width,height,GImage::IS_SOLID,0);
    objCount++;

    if(Debug::debug_enable())
        std::cout << "Crate " << objCount-1 << " created" << std::endl;
}
Crate::~Crate()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "Crate " << objCount << " destroyed" << std::endl;
}
bool Crate::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
