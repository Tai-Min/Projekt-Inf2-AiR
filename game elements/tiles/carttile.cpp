#include "carttile.h"

int CartTile::objCount = 0;
GImage *CartTile::image = nullptr;
CartTile::CartTile(int x, int y)
{
    posx = x;
    posy = y;
    width = 186;
    height = 150;
    if(!objCount)
        image = new GImage("./assets/tiles/cart.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "CartTile " << objCount-1 << " created" << std::endl;
}
CartTile::~CartTile()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "CartTile " << objCount << " destroyed" << std::endl;
}
bool CartTile::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;

}
