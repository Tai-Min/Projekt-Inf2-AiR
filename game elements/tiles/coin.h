#ifndef __COIN_H_INCLUDED__
#define __COIN_H_INCLUDED__

#include "gameobject.h"
#include "../common/ganimation.h"

class Coin : public GameObject
{
private:
    static int objCount;
    static GAnimation *animation;
public:
    Coin(int x, int y);
    ~Coin();
    int getX();
    int getY();
    bool show(int x);
};
#endif
