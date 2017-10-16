#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include <chrono>
#include <string>

#include "../common/ganimation.h"
#include "../tiles/gameobject.h"

#include "../debug.h"

class Enemy
{
private:
    enum ENEMY_STATE{//stany w ktorych moze znalezc sie przeciwnik
        IDLE = 0,
        ATTACK = 1,
        WALK = 3,
        DYING = 4
    } state = IDLE;
    enum ENEMY_DIRECTION{//kierynek w ktorym moze patrzec sie przeciwnik
        LEFT = 1,
        RIGHT =0
    } direction = LEFT;

    static int objCount;//pseudo shared pointer ktory trzyma informacje ile obiektow dzieli wskaznik do animacji
    static GAnimation *attack;
    static GAnimation *idle;
    static GAnimation *walking;
    static GAnimation *dying;

    float V = 0.2;//predkosc
    float G = 0.0003;//grawitacja
    float posx,posy,oposx,oposy;//oposx, oposy -> poprzednie pozycje przeciwnika

    int width = 96;
    int height = 96;
    int health = 2;

    bool isDying = 0;//flaga oznaczajaca ze przeciwnik jest w animacji umierania
    bool damage = 0;//flaga oznaczajaca ze przeciwnik zadal graczowi obrazenia
    bool isDead = 0;//flaga zwracajaca ze przeciwnik nie zyje
    bool damageBlock = 0;//podczas pojedynczego ataku przeciwnik powinien zadac obrazenia tylko raz
                         //ta flaga blokuje go przed zadaniem obrazen wiecej niz raz
    bool isVisible = 0;//zwraca czy przeciwnik jest na ekranie
    //uproszczenie typu zegarka
    typedef std::chrono::high_resolution_clock clock;
    //uproszczenie typu przedzialu czasu
    typedef std::chrono::duration<float, std::milli> res;
    clock::time_point start_time_walk;
    clock::time_point start_time_falling;

    void fallingTask();
    void walkTask();

public:

    Enemy(int x, int y);
    ~Enemy();

    int getX();
    int getY();
    int getHealth();
    //kolizje z otoczeniem
    int checkCollisions(GameObject * object);
    //kolizja z graczem
    int checkCollisions(int objX, int objY, int objWidth, int objHeight, int search_width);

    bool show(int x);//zwraca true jesli funkcja pokazala przeciwnika na ekranie
    bool dyingb();//zwraca czy przeciwnik umiera
    bool alive();//zwraca czy przeciwnik zyje
    bool damagePlayer();//zwraca czy gracz powinien otrzymac obrazenia
    bool visible();//zwraca czy przeciwnik jest widoczny

    void resetTimers();//resetuj timery dla utrzymania fizyki przeciwnikow
    void getPos(int & x, int & y);//zwroc pozycje x i y
    void decide();//zdecyduj gdzie powinien pojawic sie przeciwnik w nastepnej klatce
    void getBounds(int & x,int & y, int & w, int & h);//zwroc x y width i height
    void addHealth(int val);//dodaj val zycia przeciwnikowi
    void setHealth(int h);//ustaw zycie przeciwnika na h
    void setV(float v);//ustaw przedkosc przeciwnika
};
#endif
