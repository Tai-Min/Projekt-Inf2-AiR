#include "result.h"

namespace Result
{
Result::Result(bool wl){
    result = wl;

    background = new GImage("./assets/menu-background.jpg", 800, 600, GImage::IS_SOLID,0);
    background->setJustify(GImage::CENTER_CENTER);

    if(Debug::debug_enable())
        std::cout << "Result created" << std::endl;
}
Result::~Result(){
    delete background;

    if(Debug::debug_enable())
        std::cout << "Result destroyed" << std::endl;
}
void Result::show()
{
    background->show(400,300);

    setcolor(WHITE);
    outtextxy(400,200, (result == 1 ? (char*)"WYGRALES!" : (char*)"PRZEGRALES!"));
    if(cursor == MENU)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,250, "MENU");

    if(cursor == EXIT)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,300, "EXIT");
}
RESULT_CURSOR Result::getCursorState()
{
    return cursor;
}
RESULT_CURSOR operator--(RESULT_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur-1 < 0)
        cur = 1;
    else
        cur--;
    cursor = static_cast<RESULT_CURSOR>(cur);
    return cursor;
}
RESULT_CURSOR operator++(RESULT_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur+1 > 1)
        cur = 0;
    else
        cur++;
    cursor = static_cast<RESULT_CURSOR>(cur);
    return cursor;
}
void Result::moveCursor(DIRECTION direction)
{
    if(direction == UP)
        cursor--;
    else
        cursor++;
}
}
