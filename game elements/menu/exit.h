#ifndef __EXIT_H_INCLUDED__
#define __EXIT_H_INCLUDED__

#include <graphics.h>

#include "../common/gimage.h"
#include "choice.h"

namespace Exit
{

enum EXIT_CURSOR
{
    YES = 0,
    NO = 1,
};

class Exit : public Choice
{
private:
    EXIT_CURSOR cursor = NO;
    GImage *background;
public:
    Exit();
    ~Exit();
    EXIT_CURSOR getCursorState();
    void show();
    void moveCursor(DIRECTION direction);
};

}



#endif
