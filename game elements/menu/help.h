#ifndef __HELP_H_INCLUDED__
#define __HELP_H_INCLUDED__

#include <graphics.h>
#include "../common/gimage.h"

#include "../debug.h"

namespace Help
{

class Help
{
private:
    GImage *background;
public:
    Help();
    ~Help();
    void show();
};

}



#endif
