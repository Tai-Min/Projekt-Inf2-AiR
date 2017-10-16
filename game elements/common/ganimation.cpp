#include "ganimation.h"

GAnimation::GAnimation(std::string names[], int framecount, int width_, int height_, GImage::IMAGETYPE type_, int duration, bool addmirror)
{
    timer = new Timer(duration);
    timer->start();
    for(int i = 0; i < framecount; i++)
    {
        frames.push_back(new GImage(names[i], width_,height_,type_, addmirror));
    }

    if(Debug::debug_enable())
        std::cout << "GAnimation created" << std::endl;
}
GAnimation::~GAnimation()
{
    for(int i = 0; i < frames.size(); i++)
    {
        delete frames[i];
    }
    frames.clear();
    delete timer;

    if(Debug::debug_enable())
        std::cout << "GAnimation destroyed" << std::endl;
}

int GAnimation::getCurrentFrame()
{
    return current_frame;
}


bool GAnimation::ended()
{
    return ended_flag;
}


void GAnimation::reset()
{
    current_frame = 0;
}
void GAnimation::animate(int x, int y, bool mirror)
{
    ended_flag = 0;
    if(timer->done())
    {
        timer->start();
        current_frame++;
        if(current_frame >= frames.size())
        {
            ended_flag = 1;
            current_frame = 0;
        }

    }
    //jesli animacja ma byc odbita wertykalnie
    if(mirror)
        frames[current_frame]->showMirrored(x,y);
    else
        frames[current_frame]->show(x,y);
}
