#ifndef __GAMEOBJECT_H_INCLUDED__
#define __GAMEOBJECT_H_INCLUDED__

#include "../debug.h"

class GameObject
{
protected:
    int posx,posy, width, height;
public:
    GameObject();
    virtual ~GameObject();
    virtual bool show(int x) = 0;//pokaz sprite na ekranie - zwraca true jesli obiekt znajdywal sie w granicach wyswietlanego obrazu / w innym wypadku false
    void getBounds(int & x, int & y, int & width_, int & height_);
};
#endif
