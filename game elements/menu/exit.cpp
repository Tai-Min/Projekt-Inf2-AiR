#include "exit.h"

namespace Exit
{
Exit::Exit(){


    background = new GImage("./assets/menu-background.jpg", 800, 600, GImage::IS_SOLID,0);
    background->setJustify(GImage::CENTER_CENTER);

    if(Debug::debug_enable())
        std::cout << "Exit created" << std::endl;
}
Exit::~Exit(){
    delete background;

    if(Debug::debug_enable())
        std::cout << "Exit destroyed" << std::endl;
}
void Exit::show()
{
    background->show(400,300);

    setcolor(WHITE);
    outtextxy(400,200, "CZY NA PEWNO CHCESZ WYJSC?");
    if(cursor == YES)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,250, "TAK");

    if(cursor == NO)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,300, "NIE");
}
EXIT_CURSOR Exit::getCursorState()
{
    return cursor;
}
EXIT_CURSOR operator--(EXIT_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur-1 < 0)
        cur = 1;
    else
        cur--;
    cursor = static_cast<EXIT_CURSOR>(cur);
    return cursor;
}
EXIT_CURSOR operator++(EXIT_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur+1 > 1)
        cur = 0;
    else
        cur++;
    cursor = static_cast<EXIT_CURSOR>(cur);
    return cursor;
}
void Exit::moveCursor(DIRECTION direction)
{
    if(direction == UP)
        cursor--;
    else
        cursor++;
}
}
