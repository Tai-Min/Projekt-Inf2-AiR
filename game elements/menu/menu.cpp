#include "menu.h"

namespace Menu
{
Menu::Menu(){


    logo = new GImage("./assets/logo.gif", 350, 146, GImage::IS_TRANSPARENT,0);
    logo->setJustify(GImage::CENTER_CENTER);
    background = new GImage("./assets/menu-background.jpg", 800, 600, GImage::IS_SOLID,0);
    background->setJustify(GImage::CENTER_CENTER);

    std::string torchNames[3] = {
        "./assets/torch/torch1.gif",
        "./assets/torch/torch2.gif",
        "./assets/torch/torch3.gif"
    };

    torch1 = new GAnimation(torchNames,3,64,96,GImage::IS_TRANSPARENT,100,0);
    torch2 = new GAnimation(torchNames,3,64,96,GImage::IS_TRANSPARENT,100,0);

    if(Debug::debug_enable())
        std::cout << "Menu created" << std::endl;
}
Menu::~Menu(){
    delete logo;
    delete background;
    delete torch1;
    delete torch2;

    if(Debug::debug_enable())
        std::cout << "Menu destroyed" << std::endl;
}
void Menu::show()
{

    background->show(400,300);
    logo->show(400,150);
    torch1->animate(240,140, false);
    torch2->animate(510,140, false);

    if(cursor == START_GAME)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,250, "START");

    if(cursor == ABOUT)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,300, "O GRZE");

    if(cursor == EXIT)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,350, "WYJSCIE");
}
MENU_CURSOR Menu::getCursorState()
{
    return cursor;
}
MENU_CURSOR operator--(MENU_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur-1 < 0)
        cur = 2;
    else
        cur--;
    cursor = static_cast<MENU_CURSOR>(cur);
    return cursor;
}
MENU_CURSOR operator++(MENU_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur+1 > 2)
        cur = 0;
    else
        cur++;
    cursor = static_cast<MENU_CURSOR>(cur);
    return cursor;
}
void Menu::moveCursor(DIRECTION direction)
{
    if(direction == UP)
        cursor--;
    else
        cursor++;
}
}
