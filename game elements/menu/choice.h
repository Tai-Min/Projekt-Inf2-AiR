#ifndef __CHOICE_H_INCLUDED__
#define __CHOICE_H_INCLUDED__

#include "../debug.h"

class Choice
{
public:
    enum DIRECTION//mozliwe kierunki przesuniecia kursora
    {
        UP,
        DOWN
    };
    virtual void moveCursor(DIRECTION direction) = 0;
    virtual void show() = 0;
};
#endif
