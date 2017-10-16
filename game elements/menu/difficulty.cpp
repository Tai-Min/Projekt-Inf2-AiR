#include "difficulty.h"

namespace Difficulty
{
Difficulty::Difficulty(){

    background = new GImage("./assets/menu-background.jpg", 800, 600, GImage::IS_SOLID,0);
    background->setJustify(GImage::CENTER_CENTER);//ustaw pivot obrazka na srodku
    if(Debug::debug_enable())
        std::cout << "Difficulty created" << std::endl;
}
Difficulty::~Difficulty(){
    delete background;
    if(Debug::debug_enable())
        std::cout << "Difficulty destroyed" << std::endl;
}
void Difficulty::show()
{
    background->show(400,300);
    if(cursor == EASY)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,250, "LATWY");

    if(cursor == HARD)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(400,300, "TRUDNY");
}
DIFFICULTY_CURSOR Difficulty::getCursorState()
{
    return cursor;
}
DIFFICULTY_CURSOR operator--(DIFFICULTY_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur-1 < 0)
        cur = 1;
    else
        cur--;
    cursor = static_cast<DIFFICULTY_CURSOR>(cur);
    return cursor;
}
DIFFICULTY_CURSOR operator++(DIFFICULTY_CURSOR &cursor, int)
{
    int cur = static_cast<int>(cursor);
    if(cur+1 > 1)
        cur = 0;
    else
        cur++;
    cursor = static_cast<DIFFICULTY_CURSOR>(cur);
    return cursor;
}
void Difficulty::moveCursor(DIRECTION direction)
{
    if(direction == UP)
        cursor--;
    else
        cursor++;
}
}
