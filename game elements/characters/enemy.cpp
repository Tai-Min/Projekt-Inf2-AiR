#include "enemy.h"

int Enemy::objCount = 0;
GAnimation *Enemy::attack = nullptr;
GAnimation *Enemy::idle = nullptr;
GAnimation *Enemy::walking = nullptr;
GAnimation *Enemy::dying = nullptr;
Enemy::Enemy(int x, int y)
{
    posx = oposx = x;
    posy = oposy = y;
    if(!objCount)
    {
        std::string a1[10] =
        {
            "./assets/enemy/attacking/attacking1.gif",
            "./assets/enemy/attacking/attacking2.gif",
            "./assets/enemy/attacking/attacking3.gif",
            "./assets/enemy/attacking/attacking4.gif",
            "./assets/enemy/attacking/attacking5.gif",
            "./assets/enemy/attacking/attacking6.gif",
            "./assets/enemy/attacking/attacking7.gif",
            "./assets/enemy/attacking/attacking8.gif",
            "./assets/enemy/attacking/attacking9.gif",
            "./assets/enemy/attacking/attacking10.gif",
        };
        attack = new GAnimation(a1,10,width,height,GImage::IS_TRANSPARENT,85,1);

        std::string a2[10] =
        {
            "./assets/enemy/dying/dying1.gif",
            "./assets/enemy/dying/dying2.gif",
            "./assets/enemy/dying/dying3.gif",
            "./assets/enemy/dying/dying4.gif",
            "./assets/enemy/dying/dying5.gif",
            "./assets/enemy/dying/dying6.gif",
            "./assets/enemy/dying/dying7.gif",
            "./assets/enemy/dying/dying8.gif",
            "./assets/enemy/dying/dying9.gif",
            "./assets/enemy/dying/dying10.gif",
        };
        dying = new GAnimation(a2,10,width,height,GImage::IS_TRANSPARENT,75,1);

        std::string a3[10] =
        {
            "./assets/enemy/idle/idle1.gif",
            "./assets/enemy/idle/idle2.gif",
            "./assets/enemy/idle/idle3.gif",
            "./assets/enemy/idle/idle4.gif",
            "./assets/enemy/idle/idle5.gif",
            "./assets/enemy/idle/idle6.gif",
            "./assets/enemy/idle/idle7.gif",
            "./assets/enemy/idle/idle8.gif",
            "./assets/enemy/idle/idle9.gif",
            "./assets/enemy/idle/idle10.gif",
        };
        idle = new GAnimation(a3,10,width,height,GImage::IS_TRANSPARENT,75,1);

        std::string a4[10] =
        {
            "./assets/enemy/walking/walking1.gif",
            "./assets/enemy/walking/walking2.gif",
            "./assets/enemy/walking/walking3.gif",
            "./assets/enemy/walking/walking4.gif",
            "./assets/enemy/walking/walking5.gif",
            "./assets/enemy/walking/walking6.gif",
            "./assets/enemy/walking/walking7.gif",
            "./assets/enemy/walking/walking8.gif",
            "./assets/enemy/walking/walking9.gif",
            "./assets/enemy/walking/walking10.gif",
        };
        walking = new GAnimation(a4,10,width,height,GImage::IS_TRANSPARENT,75,1);
    }
    objCount++;
    start_time_falling = clock::now();
    if(Debug::debug_enable())
        std::cout << "Enemy created" << std::endl;
}
Enemy::~Enemy()
{
    objCount--;
    if(!objCount)//jesli nie ma juz zadnego przeciwnika
    {            //zwolnij zasoby
        delete attack;
        delete idle;
        delete walking;
        delete dying;
    }

    if(Debug::debug_enable())
        std::cout << "Enemy " << objCount << " destroyed" << std::endl;
}


void Enemy::fallingTask()//fizyka spadku swobodnego
{
    res now = (clock::now() - start_time_falling);
    posy+=G*now.count()*now.count()/2;
}
void Enemy::walkTask()//ruch w poziomie
{
    res now = (clock::now() - start_time_walk);
    if(direction)
        posx -= now.count()*V;
    else
        posx += now.count()*V;
    start_time_walk = clock::now();
}


int Enemy::getX()
{
    return posx;
}
int Enemy::getY()
{
    return posy;
}
int Enemy::getHealth()
{
    return health;
}
int Enemy::checkCollisions(GameObject * object)
{

    int objX,objY,objWidth,objHeight;
    object->getBounds(objX, objY, objWidth, objHeight);

    int objLeft = objX;
    int objRight = objX + objWidth;
    int objTop = objY;
    int objBottom = objY + objHeight;

    int oldLeft = oposx+30;
    int oldRight = oposx + width-30;
    int oldTop = oposy;
    int oldBottom = oposy+height;

    int currLeft = posx+30;
    int currRight = posx + width-30;
    int currTop = posy;
    int currBottom = posy+height;
    if(
            currLeft > objRight ||
            currRight < objLeft ||
            currTop > objBottom ||
            currBottom < objTop
      )
    {
        return 0;//brak kolizji
    }
    if(oldBottom < objTop && currBottom >= objTop)
    {
        posy = objTop - height - 1;//usun przeciwnika z kolizji
        start_time_falling = clock::now();
        return 1;//kolizja z gory
    }
    if(oldRight < objLeft && currRight >= objLeft)
    {
        posx = objLeft-width - 1 + 30;//usun przeciwnika z kolizji
        return 1;//kolizja z prawej
    }
    if(oldLeft >= objRight && currLeft < objRight)
    {
        posx = objRight + 1 - 30;//usun przeciwnika z kolizji
        return 1;//kolizja z prawej
    }
    return -1;//blad?
}
int Enemy::checkCollisions(int objX, int objY, int objWidth, int objHeight, int search_width)
{
    int objLeft = objX;
    int objRight = objX + objWidth;
    int objTop = objY;
    int objBottom = objY + objHeight;

    int currLeft = posx-search_width-300;
    int currRight = posx + width+search_width-300;
    int currTop = posy;
    int currBottom = posy+height;

    if((currLeft > objRight ||
            currRight < objLeft ||
            currTop > objBottom ||
            currBottom < objTop) )
    {
        state = IDLE;
        return 0;//brak kolizji
    }
    //kolizja z graczem
    //przeciwnik zwraca sie w strone gracza
    if(objLeft < currLeft+search_width)
    {
        direction = LEFT;
    }
    else if(objLeft > currLeft+search_width)
    {
        direction = RIGHT;

    }
    //gracz jest w odleglosci 250 jednostek
    //przeciwnik zaczyna gonic gracza
    if(search_width == 250)
    {
        state = WALK;
        start_time_walk = clock::now();
    }
    //gracz jest w odleglosci -20 jednostek (sprite jest troche wiekszy od modelu przeciwnika)
    //przeciwnik atakuje gracza
    else if(search_width == -20)
    {
        if(state != ATTACK)
            attack->reset();
        state = ATTACK;
    }
    return 1;
}
bool Enemy::show(int x)
{
    if(posx-x+width-30 >= 0 && posx-x+30 <= 800)
    {//jesli przeciwnik jest na ekranie
     //wyswietl odpowiednia animacje
        switch(state)
        {
        case IDLE:
            idle->animate(posx-x,posy, (bool)direction);
            break;
        case ATTACK:
            attack->animate(posx-x,posy, (bool)direction);
            if(attack->getCurrentFrame() == 5)
            {
                //jesli przeciwnik jeszcze nie zadal obrazen w 5 klatce
                //ustaw ze obrazenia zostaly zadane i zablokuj zadanie kolejnych obrazen
                //podczas tego konkretnego ataku
                if(!damageBlock)
                {
                    damageBlock = 1;
                    damage = 1;
                }

            }
            //jesli atak sie zakonczyl
            //zezwol na kolejne zadanie obrazen w nastepnym ataku
            if(attack->ended())
                damageBlock = 0;
            break;
        case WALK:
            walking->animate(posx-x,posy, (bool)direction);
            break;
        case DYING:
            dying->animate(posx-x,posy, (bool)direction);
            //jesli animacja umierania sie zakonczyla
            //ustaw flage ze przeciwnik jest martwy
            if(dying->getCurrentFrame() == 9)
                isDead = 1;
            break;
        }
        isVisible = 1;
        return 1;
    }
    else if(isDying)
        isDead = 1;
    isVisible = 0;
    return 0;
}
bool Enemy::dyingb()
{
    return isDying;
}
bool Enemy::alive()
{
    return !isDead;
}
bool Enemy::damagePlayer()
{
    bool t = damage;
    damage = 0;
    return t;
}
bool Enemy::visible()
{
    return isVisible;
}
void Enemy::resetTimers()
{
    start_time_falling = clock::now();
    start_time_walk = clock::now();
}
void Enemy::getPos(int & x, int & y)
{
    x = posx;
    y = posy;
}
void Enemy::decide()
{
    //zapisz porzednie pozycje przeciwnika
    oposx = posx;
    oposy = posy;
    fallingTask();
    switch(state)
    {
    case WALK:
        walkTask();
        break;
    }
}
void Enemy::getBounds(int & x,int & y, int & w, int & h)
{
    x = posx;
    y = posy;
    w = width;
    h = height;
}
void Enemy::addHealth(int val)
{
    health+=val;
    if(!health)
    {
        state = DYING;
        isDying = 1;
    }
}
void Enemy::setHealth(int h)
{
    health = h;
}
void Enemy::setV(float v)
{
    V = v;
}











