#ifndef __DIFFICULTY_H_INCLUDED__
#define __DIFFICULTY_H_INCLUDED__

#include <graphics.h>

#include "../common/gimage.h"
#include "choice.h"

namespace Difficulty
{

enum DIFFICULTY_CURSOR//mozliwe wybory w konkretnym oknie
{
    EASY = 0,
    HARD = 1,
};

class Difficulty : public Choice
{
private:
    DIFFICULTY_CURSOR cursor = EASY;
    GImage *background;
public:
    Difficulty();
    ~Difficulty();
    DIFFICULTY_CURSOR getCursorState();//zwroc aktualna pozycje kursora
    void show();
    void moveCursor(DIRECTION direction);//przesun kursor o 1 we wskazanym kierunku
};

}



#endif
