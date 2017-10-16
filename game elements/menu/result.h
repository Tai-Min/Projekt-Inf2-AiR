#ifndef __RESULT_H_INCLUDED__
#define __RESULT_H_INCLUDED__

#include <graphics.h>
#include "../common/gimage.h"
#include "choice.h"

#include "../debug.h"

namespace Result
{

enum RESULT_CURSOR
{
    MENU = 0,
    EXIT = 1,
};

class Result : public Choice
{
private:
    RESULT_CURSOR cursor = MENU;
    GImage *background;
    bool result;
public:
    Result(bool wl);
    ~Result();
    RESULT_CURSOR getCursorState();
    void show();
    void moveCursor(DIRECTION direction);
};

}



#endif
