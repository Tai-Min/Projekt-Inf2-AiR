#ifndef __GANIMATION_H_INCLUDED__
#define __GANIMATION_H_INCLUDED__

#include <vector>

#include "gimage.h"
#include "timer.h"

#include "../debug.h"

class GAnimation
{
private:

    int current_frame = 0;//aktualna klatka animacji
    int width;
    int height;
    bool ended_flag = 0;//flaga ustawiana kiedy skonczy sie animacja

    GImage::IMAGETYPE type;
    Timer *timer;//timer ktorego tick sygnalizuje zmiane aktualnej klatki
    std::vector<GImage*> frames;//wektor trzymajacy klatki

public:
    ~GAnimation();
    GAnimation(std::string names[],int framecount, int width_, int height_, GImage::IMAGETYPE type_, int duration, bool addmirror);

    int getCurrentFrame();

    bool ended();//zwraca czy animacja sie zakonczyla

    void reset();//ustawia current_frame na 0
    void animate(int x, int y, bool mirror);//wyswietl aktualna klatke animacji
};
#endif
