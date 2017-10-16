#ifndef __HOUSE3_H_INCLUDED__
#define __HOUSE3_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class House3 : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    House3(int x, int y);
    ~House3();
    bool show(int x);
};
#endif
