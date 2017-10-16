#include "info.h"

namespace Info
{
Info::Info(){
    background = new GImage("./assets/menu-background.jpg", 800, 600, GImage::IS_SOLID,0);
    background->setJustify(GImage::CENTER_CENTER);

    if(Debug::debug_enable())
        std::cout << "Info created" << std::endl;
}
Info::~Info(){
    delete background;

    if(Debug::debug_enable())
        std::cout << "Info destroyed" << std::endl;
}
void Info::show()
{
    background->show(400,300);
    setcolor(WHITE);
    outtextxy(400,100, "Autor: Mateusz Pajak");
    outtextxy(400,125,"Wszystkie assety uzyte w grze");

    outtextxy(400,150, "pochodza z opengameart.org");
    outtextxy(400,175, "i sa uzyte zgodnie z licencja ");

    outtextxy(400,200, "Creative Commons Attribution 3.0");
    outtextxy(400,500, "aby wrocic do menu wcisnij ESC");
}
}
