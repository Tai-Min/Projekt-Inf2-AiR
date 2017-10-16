#ifndef __HOUSE2_H_INCLUDED__
#define __HOUSE2_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class House2 : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    House2(int x, int y);
    ~House2();
    bool show(int x);
};
#endif
