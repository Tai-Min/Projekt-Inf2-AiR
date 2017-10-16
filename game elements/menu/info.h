#ifndef __INFO_H_INCLUDED__
#define __INFO_H_INCLUDED__

#include <graphics.h>
#include "../common/gimage.h"

#include "../debug.h"

namespace Info
{

class Info
{
private:
    GImage *background;
public:
    Info();
    ~Info();
    void show();
};

}



#endif
