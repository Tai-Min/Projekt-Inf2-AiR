#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <cmath>
#include <chrono>
#include <string>

#include "../common/kevent.h"
#include "../tiles/gameobject.h"
#include "enemy.h"

#include "../debug.h"

class Player
{
private:
    enum PLAYER_DIRECTION{
        LEFT = 1,
        RIGHT =0
    } direction = RIGHT;
    enum PLAYER_STATE{
        IDLE = 0,
        WALK = 1,
        ATTACK = 2,
        DIE = 3,
    } state = IDLE;

    float posx = 300;//referencyjna pozycja gracza na ekranie
    float posy = 483;
    float V = 0.3;//predkosc
    float G = 0.0003;//grawitacja

    int hardcodedx = 300;//stala pozycja gracza na ekranie
    int width = 96;
    int height = 96;
    int health = 3;

    bool spawnArrow = 0;//flaga oznaczajaca ze gracz wystrzelil strzale
    bool spawnArrowBlock = 0;//flaga blokujaca wystrzelenie wiecej niz 1 strzaly na raz
    bool idleanim = 0;//jedna z dwoch mozliwych animacji stanu idle
    bool isDead = 0;//flaga oznaczajaca ze gracz umarl

    GAnimation *idle1;
    GAnimation *idle2;
    GAnimation *walk;
    GAnimation *die;
    GAnimation *attack;

    //uproszczenie typu zegarka
    typedef std::chrono::high_resolution_clock clock;
    //uproszczenie typu przedzialu czasu
    typedef std::chrono::duration<float, std::milli> res;
    clock::time_point start_time_walk;
    clock::time_point start_time_falling;

    void rollIdle();//wylosuj aktualna animacje idle
    void idleAnim();//animuj aktualna animacje idle
    void walkTask();
    void fallingTask();

public:
    enum PLAYER_COLLISION{//mozliwe kolizje gracza
        PORTAL = 2,
        OBJECT = 1,
        COIN = 3
    };

    Player();
    ~Player();

    //sprawdz kolizje gracza z obiektem
    int checkCollisions(GameObject * object, int oldx, int oldy, PLAYER_COLLISION type);
    //sprawdz kolizje gracza z przeciwnikiem
    int checkCollisions(Enemy * object, int oldx, int oldy);
    int getHealth();
    int getW();//zwroc width
    int getH();//zwroc height
    int getX();
    int getY();

    bool shouldSpawnArrow();//zwroc czy gracz wystrzelil strzale
    bool getDirection();//zwroc kierunek gracza
    bool died();//sprawdz czy gracz umarl

    void getPos(int & x, int & y);//zwroc referencyjna pozycje gracza
    void decide(KEvent & keyboard);//zdecyduj polozenie gracza na podstawie fizyki i akcji gracza
    void setY(int y);
    void setX(int x);
    void setHealth(int h);
    void show();
    void resetTimers();//resetuj timery fizyki
    void addHealth(int j);
};
#endif
