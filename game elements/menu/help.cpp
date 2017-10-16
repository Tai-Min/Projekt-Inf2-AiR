#include "help.h"

namespace Help
{
Help::Help(){
    background = new GImage("./assets/menu-background.jpg", 800, 600, GImage::IS_SOLID,0);
    background->setJustify(GImage::CENTER_CENTER);
    if(Debug::debug_enable())
        std::cout << "Help created" << std::endl;
}
Help::~Help(){
    delete background;

    if(Debug::debug_enable())
        std::cout << "Help destroyed" << std::endl;
}
void Help::show()
{
    background->show(400,300);
    setcolor(WHITE);
    outtextxy(400,100, "strzalki lewo/prawo -> ruch postaci ");
    outtextxy(400,125,"w odpowiednim kierunku");

    outtextxy(400,175, "strzalka w gore -> w miejscach oznaczonych");
    outtextxy(400,200, "szara strzalka przenosi postac w inne miejsce");

    outtextxy(400,250, "spacja -> atak");

    outtextxy(400,300, "F2 -> save");

    outtextxy(400,350, "F3 -> load");

    outtextxy(400,400, "aby wygrac zbierz 20 monet");

    outtextxy(400,500, "aby wrocic do gry wcisnij F1/ESC");
}
}
