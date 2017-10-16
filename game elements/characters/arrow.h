#ifndef __ARROW_H_INCLUDED__
#define __ARROW_H_INCLUDED__

#include <chrono>

#include "../common/gimage.h"
#include "../tiles/gameobject.h"
#include "enemy.h"

#include "../debug.h"

class Arrow
{
private:
    static int objCount;//pseudo shared pointer ktory trzyma informacje ile obiektow dzieli wskaznik do image
    static GImage *image;

    float posx;
    float posy;
    float A = 0.00003;//przyspieszenie w poziomie

    int width;
    int height;

    bool direction;//kierunek strzaly

    //uproszczenie typu zegarka
    typedef std::chrono::high_resolution_clock clock;
    //uproszczenie typu przedzialu czasu
    typedef std::chrono::duration<float, std::milli> res;
    clock::time_point start_time;

public:
    //wczytaj obrazek strzaly
    static void loadArrows();
    //usun obrazek strzaly
    static void deleteArrows();

    Arrow(int x, int y, bool dir);
    ~Arrow();

    //sprawdz kolizje z obiektem
    bool checkCollisions(GameObject * object);
    //sprawdz kolizje z przeciwnikiem
    bool checkCollisions(Enemy * enemy);
    bool show(int x);
    //zdecyduj gdzie ma sie pojawic strzala w nastepnej klatce
    void decide();
};
#endif
