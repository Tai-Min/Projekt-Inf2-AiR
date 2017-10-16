#include "barrel.h"

int Barrel::objCount = 0;
GImage *Barrel::image = nullptr;
Barrel::Barrel(int x, int y)
{
    posx = x;
    posy = y;
    width = 48;
    height = 60;
    if(!objCount)//jesli nie istnieje zaden obiekt tej klasy - wczytaj sprite
        image = new GImage("./assets/barrel.gif",width,height,GImage::IS_TRANSPARENT,0);
    objCount++;
    if(Debug::debug_enable())
        std::cout << "Barrel " << objCount-1 << " created" << std::endl;
}
Barrel::~Barrel()
{
    objCount--;
    if(!objCount)//wszystkie obiekty tej klasy zostaly usuniete - skasuj sprite
        delete image;

    if(Debug::debug_enable())
        std::cout << "Barrel " << objCount << " destroyed" << std::endl;
}
bool Barrel::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      image->show(posx-x,posy);
      return 1;
    }
    return 0;
}
