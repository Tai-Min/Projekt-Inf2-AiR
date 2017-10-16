#ifndef __HOUSE1_H_INCLUDED__
#define __HOUSE1_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class House1 : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    House1(int x, int y);
    ~House1();
    bool show(int x);
};
#endif
