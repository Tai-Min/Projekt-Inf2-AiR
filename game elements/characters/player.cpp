#include "player.h"

Player::Player()
{
    srand(time(NULL));
    std::string anim1[10] =
    {
        "./assets/player/idle1/idle11.gif",
        "./assets/player/idle1/idle12.gif",
        "./assets/player/idle1/idle13.gif",
        "./assets/player/idle1/idle14.gif",
        "./assets/player/idle1/idle15.gif",
        "./assets/player/idle1/idle16.gif",
        "./assets/player/idle1/idle17.gif",
        "./assets/player/idle1/idle18.gif",
        "./assets/player/idle1/idle19.gif",
        "./assets/player/idle1/idle110.gif",
    };
    idle1 = new GAnimation(anim1,10,width,height,GImage::IS_TRANSPARENT,75,1);

    std::string anim2[10] =
    {
        "./assets/player/idle2/idle21.gif",
        "./assets/player/idle2/idle22.gif",
        "./assets/player/idle2/idle23.gif",
        "./assets/player/idle2/idle24.gif",
        "./assets/player/idle2/idle25.gif",
        "./assets/player/idle2/idle26.gif",
        "./assets/player/idle2/idle27.gif",
        "./assets/player/idle2/idle28.gif",
        "./assets/player/idle2/idle29.gif",
        "./assets/player/idle2/idle210.gif",
    };
    idle2 = new GAnimation(anim2,10,width,height,GImage::IS_TRANSPARENT,75,1);

    std::string anim3[10] =
    {
        "./assets/player/walking/walking1.gif",
        "./assets/player/walking/walking2.gif",
        "./assets/player/walking/walking3.gif",
        "./assets/player/walking/walking4.gif",
        "./assets/player/walking/walking5.gif",
        "./assets/player/walking/walking6.gif",
        "./assets/player/walking/walking7.gif",
        "./assets/player/walking/walking8.gif",
        "./assets/player/walking/walking9.gif",
        "./assets/player/walking/walking10.gif",
    };
    walk = new GAnimation(anim3,10,width,height,GImage::IS_TRANSPARENT,75,1);

    std::string anim4[10] =
    {
        "./assets/player/dying/dying1.gif",
        "./assets/player/dying/dying2.gif",
        "./assets/player/dying/dying3.gif",
        "./assets/player/dying/dying4.gif",
        "./assets/player/dying/dying5.gif",
        "./assets/player/dying/dying6.gif",
        "./assets/player/dying/dying7.gif",
        "./assets/player/dying/dying8.gif",
        "./assets/player/dying/dying9.gif",
        "./assets/player/dying/dying10.gif",
    };
    die = new GAnimation(anim4,10,width,height,GImage::IS_TRANSPARENT,75,1);

    std::string anim5[10] =
    {
        "./assets/player/attacking/attacking1.gif",
        "./assets/player/attacking/attacking2.gif",
        "./assets/player/attacking/attacking3.gif",
        "./assets/player/attacking/attacking4.gif",
        "./assets/player/attacking/attacking5.gif",
        "./assets/player/attacking/attacking6.gif",
        "./assets/player/attacking/attacking7.gif",
        "./assets/player/attacking/attacking8.gif",
        "./assets/player/attacking/attacking9.gif",
        "./assets/player/attacking/attacking10.gif",
    };
    attack = new GAnimation(anim5,10,width,height,GImage::IS_TRANSPARENT,85,1);

    start_time_falling = clock::now();

    if(Debug::debug_enable())
        std::cout << "Player created" << std::endl;


}
Player::~Player()
{
    delete idle1;
    delete idle2;
    delete walk;
    delete die;
    delete attack;

    if(Debug::debug_enable())
        std::cout << "Player destroyed" << std::endl;
}


void Player::rollIdle()//wylosuj 1 z 2 animacji idle
{
    int t = rand() % 20;
    if(t < 19)
        idleanim = 0;
    else
        idleanim = 1;
}
void Player::idleAnim()//animuj odpowiednia animacje idle
{
    if(!idleanim)
    {
        idle1->animate(hardcodedx,(int)posy, direction);
        if(idle1->ended())
        {
            rollIdle();
        }
    }
    else
    {
        idle2->animate(hardcodedx,(int)posy, direction);
        if(idle2->ended())
        {
            rollIdle();
        }
    }
}
void Player::walkTask()
{
    res now = (clock::now() - start_time_walk);
    if(direction)
        posx -= now.count()*V;
    else
        posx += now.count()*V;
    start_time_walk = clock::now();
}
void Player::fallingTask()
{
    res now = (clock::now() - start_time_falling);
    posy+=G*now.count()*now.count()/2;
}

int Player::checkCollisions(GameObject * object, int oldx, int oldy, PLAYER_COLLISION type)
{
    int objX,objY,objWidth,objHeight;
    object->getBounds(objX, objY, objWidth, objHeight);

    int objLeft = objX-hardcodedx;
    int objRight = objX + objWidth-hardcodedx;
    int objTop = objY;
    int objBottom = objY + objHeight;

    int oldLeft = oldx+30;
    int oldRight = oldx + width-30;
    int oldTop = oldy;
    int oldBottom = oldy+height;

    int currLeft = posx+30;
    int currRight = posx + width-30;
    int currTop = posy;
    int currBottom = posy+height;
    if((currLeft > objRight ||
            currRight < objLeft ||
            currTop > objBottom ||
            currBottom < objTop) )
    {
        return 0;//brak kolizji
    }
    //jak kolizja z obiektem to wyrzuc postac z kolizji w odpowiednim kierunku
    if(type == OBJECT)//kolizja z otoczeniem
    {
        if(oldBottom < objTop && currBottom >= objTop)
        {
            posy = objTop - height - 1;
            start_time_falling = clock::now();
            return 1;
        }
        if(oldRight < objLeft && currRight >= objLeft)
        {
            posx = objLeft-width-1+30;
            return 1;
        }
        if(oldLeft >= objRight && currLeft < objRight)
        {
            posx = objRight + 1-30;
            return 1;
        }
        if(oldTop >= objBottom && currTop < objBottom)
        {
            posy = objBottom + 1;
            return 1;
        }
    }
    else if(type == PORTAL)//portal
    {
        return 2;
    }
    else if(type == COIN)//moneta
    {
        return 3;
    }
    return -1;//blad?
}

int Player::checkCollisions(Enemy * object, int oldx, int oldy)
{
    int objX,objY,objWidth,objHeight;
    object->getBounds(objX, objY, objWidth, objHeight);

    int objLeft = objX-hardcodedx;
    int objRight = objX + objWidth-hardcodedx;
    int objTop = objY;
    int objBottom = objY + objHeight;

    int oldLeft = oldx+30;
    int oldRight = oldx + width-30;

    int currLeft = posx+30;
    int currRight = posx + width-30;
    int currTop = posy;
    int currBottom = posy+height;

    if((currLeft > objRight ||
            currRight < objLeft ||
            currTop > objBottom ||
            currBottom < objTop) )
    {
        return 0;//brak kolizji
    }
    //jak kolizja z przeciwnikiem to cofnij gracza w odpowiednim kierunku
    if(oldRight < objLeft && currRight >= objLeft)
    {
        posx = objLeft-width-1+30;
        return 1;
    }
    if(oldLeft >= objRight && currLeft < objRight)
    {
        posx = objRight + 1-30;
        return 1;
    }
    return -1;//blad?
}
int Player::getHealth()
{
    return health;
}
int Player::getW()
{
    return width;
}
int Player::getH()
{
    return height;
}
int Player::getX()
{
    return posx;
}
int Player::getY()
{
    return posy;
}


bool Player::shouldSpawnArrow()
{
    bool t = spawnArrow;
    spawnArrow = 0;
    return t;
}
bool Player::getDirection()
{
    return (bool)direction;
}
bool Player::died()
{
    return isDead;
}


void Player::getPos(int & x, int & y)
{
    x = posx;
    y = posy;
}
void Player::decide(KEvent & keyboard)
{
    fallingTask();
    switch(state)
    {
    case IDLE:
        if(keyboard.RightArrowPressed())
        {
            direction = RIGHT;
            start_time_walk = clock::now();
            state = WALK;
        }
        if(keyboard.LeftArrowPressed())
        {
            direction = LEFT;
            start_time_walk = clock::now();
            state = WALK;
        }
        if(keyboard.SpacebarPressed())
        {
            state = ATTACK;
        }
        break;
    case WALK:
        if(keyboard.RightArrowPressed())
        {
            direction = RIGHT;
        }
        else if(keyboard.LeftArrowPressed())
        {
            direction = LEFT;
        }
        else
        {
            rollIdle();
            state = IDLE;
        }
        walkTask();
        break;
    case ATTACK:
        if(attack->getCurrentFrame() == 6 && !spawnArrowBlock)
        {
            spawnArrow = 1;
            spawnArrowBlock = 1;
        }
        if(attack->ended())
        {
            state = IDLE;
            spawnArrowBlock = 0;
        }
        break;
    }
}
void Player::setY(int y)
{
    posy = y;
}
void Player::setX(int x)
{
    posx = x;
}
void Player::setHealth(int h)
{
    health = h;
}
void Player::show()
{
    switch(state)
    {
    case IDLE:
        idleAnim();
        break;
    case WALK:
        walk->animate(hardcodedx,(int)posy, direction);
        break;
    case ATTACK:
        attack->animate(hardcodedx,(int)posy, direction);
        break;
    case DIE:
        die->animate(hardcodedx, (int)posy, direction);
        if(die->ended())
            isDead = 1;
        break;
    }
}
void Player::resetTimers()
{
    start_time_falling = clock::now();
    start_time_walk = clock::now();
}
void Player::addHealth(int j)
{
    health+=j;
    if(health == 0)
    {
        state = DIE;
    }
}
