#ifndef __CARTTILE_H_INCLUDED__
#define __CARTTILE_H_INCLUDED__

#include "gameobject.h"
#include "../common/gimage.h"

class CartTile : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    CartTile(int x, int y);
    ~CartTile();
    bool show(int x);
};
#endif
