#ifndef __PORTAL_H_INCLUDED__
#define __PORTAL_H_INCLUDED__

#include "gameobject.h"
#include "../common/ganimation.h"

class Portal : public GameObject
{
private:
    static int objCount;
    static GAnimation *anim;
    int Y = 0;
public:
    Portal(int x, int y, int teleportY);
    ~Portal();
    bool show(int x);
    int getPortalY();
};
#endif
