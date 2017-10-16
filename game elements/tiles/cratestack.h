#ifndef __CRATESTACK_H_INCLUDED__
#define __CRATESTACK_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class CrateStack : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    CrateStack(int x, int y);
    ~CrateStack();
    bool show(int x);
};
#endif
