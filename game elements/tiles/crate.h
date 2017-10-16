#ifndef __CRATE_H_INCLUDED__
#define __CRATE_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class Crate : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    Crate(int x, int y);
    ~Crate();
    bool show(int x);
};
#endif
