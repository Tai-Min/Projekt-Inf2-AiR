#include "coin.h"

int Coin::objCount = 0;
GAnimation *Coin::animation = nullptr;
Coin::Coin(int x, int y)
{
    posx = x;
    posy = y;
    width = 32;
    height = 32;
    if(!objCount)
    {
        std::string names[9] = {
            "./assets/coin/coin1.gif",
            "./assets/coin/coin2.gif",
            "./assets/coin/coin3.gif",
            "./assets/coin/coin4.gif",
            "./assets/coin/coin5.gif",
            "./assets/coin/coin6.gif",
            "./assets/coin/coin7.gif",
            "./assets/coin/coin8.gif",
            "./assets/coin/coin9.gif"
        };
        animation = new GAnimation(names,9,width,height,GImage::IS_TRANSPARENT,100,0);
    }

    objCount++;
    if(Debug::debug_enable())
        std::cout << "Coin " << objCount-1 << " created" << std::endl;
}
Coin::~Coin()
{
    objCount--;
    if(!objCount)
        delete animation;

    if(Debug::debug_enable())
        std::cout << "Coin " << objCount << " destroyed" << std::endl;
}
int Coin::getX()
{
    return posx;
}
int Coin::getY()
{
    return posy;
}
bool Coin::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
      animation->animate(posx-x,posy,0);
      return 1;
    }
    return 0;

}
