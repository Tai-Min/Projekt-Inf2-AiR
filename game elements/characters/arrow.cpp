#include "arrow.h"

int Arrow::objCount = 0;
GImage * Arrow::image = nullptr;

Arrow::Arrow(int x, int y, bool dir)
{
    direction = dir;
    posx = x+335;
    posy = y+30;
    width = 58;
    height = 10;
    start_time = clock::now();
    objCount++;
    if(Debug::debug_enable())
        std::cout << "Arrow " << objCount-1 << " created" << std::endl;
}
Arrow::~Arrow()
{
    objCount--;
    if(Debug::debug_enable())
        std::cout << "Arrow " << objCount << " destroyed" << std::endl;
}


void Arrow::loadArrows()
{
    image = new GImage("./assets/archerarrow/arrow.gif",58,10,GImage::IS_TRANSPARENT,1);
}
void Arrow::deleteArrows()
{
    delete image;
}


bool Arrow::checkCollisions(Enemy * object)
{
    int objX,objY,objWidth,objHeight;
    object->getBounds(objX, objY, objWidth, objHeight);

    int objLeft = objX+30;
    int objRight = objX + objWidth-30;
    int objTop = objY;
    int objBottom = objY + objHeight;

    int currLeft = posx;
    int currRight = posx + width;
    int currTop = posy;
    int currBottom = posy+height;
    if((currLeft > objRight ||
            currRight < objLeft ||
            currTop > objBottom ||
            currBottom < objTop) )
    {
        return 0;//brak kolizji
    }
    return 1;//kolizja z przeciwnikiem
}
bool Arrow::checkCollisions(GameObject * object)
{
    int objX,objY,objWidth,objHeight;
    object->getBounds(objX, objY, objWidth, objHeight);

    int objLeft = objX;
    int objRight = objX + objWidth;
    int objTop = objY;
    int objBottom = objY + objHeight;

    int currLeft = posx;
    int currRight = posx + width;
    int currTop = posy;
    int currBottom = posy+height;
    if((currLeft > objRight ||
            currRight < objLeft ||
            currTop > objBottom ||
            currBottom < objTop) )
    {
        return 0;//brak kolizji
    }
    return 1;//kolizja z obiektem
}
bool Arrow::show(int x)
{
    if(posx-x+width >= 0 && posx-x <= 800)
    {
        if(direction)
            image->showMirrored(posx-x,posy);
        else
            image->show(posx-x,posy);
      return 1;
    }
    return 0;

}

void Arrow::decide()
{
    res now = (clock::now() - start_time);


    float val  = now.count()-A*now.count()*now.count()/2;
    if(direction == 1)
        posx=posx-val;
    else
        posx=posx+val;
        start_time = clock::now();
}


