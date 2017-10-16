#include "groundtile.h"

int GroundTile::objCount = 0;
GImage *GroundTile::image = nullptr;
GroundTile::GroundTile(int x, int y)
{
    posx = x;
    posy = y;
    width = 60;
    height = 76;
    if(!objCount)
        image = new GImage("./assets/tiles/ground.jpg",60,76,GImage::IS_SOLID,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "GroundTile " << objCount-1 << " created" << std::endl;
}
GroundTile::~GroundTile()
{
    objCount--;
    if(!objCount)
        delete image;
    if(Debug::debug_enable())
        std::cout << "GroundTile " << objCount << " destroyed" << std::endl;
}
bool GroundTile::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;

}
