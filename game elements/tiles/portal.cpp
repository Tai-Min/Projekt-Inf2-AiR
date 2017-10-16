#include "portal.h"

int Portal::objCount = 0;
GAnimation *Portal::anim = nullptr;
Portal::Portal(int x, int y, int teleportY)
{
    posx = x;
    posy = y;
    width = 60;
    height = 76;
    Y = teleportY;
    if(!objCount)
    {
        std::string names[20] =
        {
            "./assets/arrow/arr1.gif",
            "./assets/arrow/arr2.gif",
            "./assets/arrow/arr3.gif",
            "./assets/arrow/arr4.gif",
            "./assets/arrow/arr5.gif",
            "./assets/arrow/arr6.gif",
            "./assets/arrow/arr7.gif",
            "./assets/arrow/arr8.gif",
            "./assets/arrow/arr9.gif",
            "./assets/arrow/arr10.gif",
            "./assets/arrow/arr11.gif",
            "./assets/arrow/arr12.gif",
            "./assets/arrow/arr13.gif",
            "./assets/arrow/arr14.gif",
            "./assets/arrow/arr15.gif",
            "./assets/arrow/arr16.gif",
            "./assets/arrow/arr17.gif",
            "./assets/arrow/arr18.gif",
            "./assets/arrow/arr19.gif",
            "./assets/arrow/arr20.gif",
        };
        anim = new GAnimation(names,20,42,56,GImage::IS_TRANSPARENT,50,0);
    }

    objCount++;
    if(Debug::debug_enable())
        std::cout << "Portal " << objCount-1 << " created" << std::endl;
}
int Portal::getPortalY()
{
    return Y;
}
Portal::~Portal()
{
    objCount--;
    if(!objCount)
        delete anim;
    if(Debug::debug_enable())
        std::cout << "Portal " << objCount << " destroyed" << std::endl;
}
bool Portal::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
        anim->animate(posx-x,posy,0);
        return 1;
    }
    return 0;

}
