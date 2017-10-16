#ifndef __LAMP_H_INCLUDED__
#define __LAMP_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class Lamp : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    Lamp(int x, int y);
    ~Lamp();
    bool show(int x);
};
#endif
