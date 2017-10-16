#ifndef __WELL_H_INCLUDED__
#define __WELL_H_INCLUDED__

#include "../tiles/gameobject.h"
#include "../common/gimage.h"

class Well : public GameObject
{
private:
    static int objCount;
    static GImage *image;
public:
    Well(int x, int y);
    ~Well();
    bool show(int x);
};
#endif
