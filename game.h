#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <graphics.h>
#include <fstream>

#include "./game elements/menu/menu.h"
#include "./game elements/menu/difficulty.h"
#include "./game elements/menu/help.h"
#include "./game elements/menu/info.h"
#include "./game elements/menu/exit.h"
#include "./game elements/menu/result.h"
#include "./game elements/menu/gameworld.h"
#include "./game elements/common/kevent.h"
#include "game elements/common/timer.h"

#include "./game elements/debug.h"

class Game{
private:
    //kazdy stan gry to osobny obiekt
    Menu::Menu *menu;
    Difficulty::Difficulty  *difficulty;
    GameWorld *game;
    Exit::Exit *exit;
    Help::Help *help;
    Info::Info *info;
    Result::Result *result;
    //obiekt pobierajacy zdarzenia z klawiatury
    KEvent keyboard;
    //timer ograniczajacy wcisniecia przyciskow do 1 per 200ms
    Timer *KEventDelay;
    enum GAME_STATE{//stany w ktorych moze znalezc sie gra
        MENU,
        INFO,
        DIFFCULTY,
        GAME,
        HELP,
        EXIT,
        RESULT
    } gstate = MENU, previous_gstate = MENU;
    bool menuTask(bool inputEnabled);
    bool difficultyTask(bool inputEnabled);
    bool gameTask(bool inputEnabled);
    bool exitTask(bool inputEnabled);
    bool helpTask(bool inputEnabled);
    bool infoTask(bool inputEnabled);
    bool resultTask(bool inputEnabled);
    bool KEventReady();//zwraca czy timer KEventDelay zezwala na odczyt z klawiatury
    bool resetGameTimers = 0;//flaga oznaczajace ze jakiekolwiek timery w grze (nie w menusach) powinny zostac zresetowane
    bool kill = 0;//flaga do zamkniêcia programu
public:
    Game();
    ~Game();
    bool run();//zwraca o jesli gra sie zakonczyla
};

#endif
