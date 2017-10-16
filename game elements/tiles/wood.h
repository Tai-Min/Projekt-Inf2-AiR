#ifndef __WOOD_H_INCLUDED__
#define __WOOD_H_INCLUDED__

#include "gameobject.h"
#include "../common/gimage.h"

class Wood : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    Wood(int x, int y);
    ~Wood();
    bool show(int x);
};
#endif
