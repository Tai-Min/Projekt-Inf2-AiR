#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include <graphics.h>

#include "../common/gimage.h"
#include "../common/ganimation.h"
#include "choice.h"

namespace Menu
{

enum MENU_CURSOR
{
    START_GAME = 0,
    ABOUT = 1,
    EXIT = 2,
};

class Menu : public Choice
{
private:
    MENU_CURSOR cursor = START_GAME;
    GImage *logo;
    GImage *background;

    GAnimation *torch1;
    GAnimation *torch2;
public:
    Menu();
    ~Menu();
    MENU_CURSOR getCursorState();
    void show();
    void moveCursor(DIRECTION direction);
};

}



#endif
