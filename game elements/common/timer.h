#ifndef __TIMER_H_INCLUDED__
#define __TIMER_H_INCLUDED__

#include <chrono>

#include "../debug.h"

class Timer{
private:
    int timer_duration = 0;//czas trwania timera w milisekundach
    bool started = 0;//flaga oznaczajaca czy timer wystartowal
    void reset();//reset timera

    //uproszczenie typu zegarka
    typedef std::chrono::high_resolution_clock clock;
    //uproszczenie typu przedzialu czasu
    typedef std::chrono::duration<float, std::milli> time;
    clock::time_point start_time;

public:
    Timer(int duration_);
    ~Timer();

    bool done();
    void start();
    void stop();
};
#endif
