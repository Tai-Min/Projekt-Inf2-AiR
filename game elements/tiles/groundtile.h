#ifndef __GROUNDTILE_H_INCLUDED__
#define __GROUNDTILE_H_INCLUDED__

#include "gameobject.h"
#include "../common/gimage.h"

class GroundTile : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    GroundTile(int x, int y);
    ~GroundTile();
    bool show(int x);
};
#endif
