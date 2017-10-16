#include "timer.h"

Timer::Timer(int duration_)
{
    timer_duration = duration_;
    if(Debug::debug_enable())
        std::cout << "Timer created" << std::endl;
}
Timer::~Timer()
{
    if(Debug::debug_enable())
        std::cout << "Timer destroyed" << std::endl;
}


void Timer::reset()
{
    start_time = clock::now();
}


bool Timer::done()
{
    if(!started)
        return 1;

    time t = clock::now()-start_time;
    if(t.count() >= timer_duration)
    {
        stop();
        //reset();
        return 1;
    }
    return 0;
}
void Timer::start()
{
    started = 1;
    reset();
}
void Timer::stop()
{
    started = 0;
}

