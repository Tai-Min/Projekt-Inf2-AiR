#include "gameobject.h"

GameObject::GameObject()
{
    if(Debug::debug_enable())
        std::cout << "GameObject created" << std::endl;
}
GameObject::~GameObject()
{
    if(Debug::debug_enable())
        std::cout << "GameObject destroyed" << std::endl;
}

void GameObject::getBounds(int & x, int & y, int & width_, int & height_)
{
    x = posx;
    y = posy;
    width_ = width;
    height_ = height;
}
