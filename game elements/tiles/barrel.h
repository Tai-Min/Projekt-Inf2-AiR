#ifndef __BARREL_H_INCLUDED__
#define __BARREL_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class Barrel : public GameObject
{
private:
    static int objCount;//pseudo shared pointer ktory trzyma informacje ile obiektow dzieli wskaznik do image
    static GImage *image;
public:
    Barrel(int x, int y);
    ~Barrel();
    bool show(int x);
};
#endif
