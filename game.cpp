#include "game.h"
#define WW 800
#define WH 600

Game::Game()
{
    int err;
    initwindow(WW, WH, "PROJEKT The Game", (getmaxwidth()-WW)/2, (getmaxheight()-WH)/2);
    err = graphresult();
    if(err != grOk)
    {
        std::cout << grapherrormsg(err) << std::endl;
        getch();
        kill = 1;
    }

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);//jedna z tych funkcji ma wyciek pamieci
    settextjustify(CENTER_TEXT, TOP_TEXT);//z jakiegos powodu
    KEventDelay = new Timer(200);
    menu = new Menu::Menu;

    if(Debug::debug_enable())
        std::cout << "Game created" << std::endl;
}
Game::~Game()
{
    delete KEventDelay;

    if(Debug::debug_enable())
        std::cout << "Game destroyed" << std::endl;
}
bool Game::KEventReady()
{
    if(!KEventDelay->done())
        return 0;
    return 1;
}
bool Game::helpTask(bool inputEnabled)
{
    if(inputEnabled)
    {
        //wroc do gry
        if(keyboard.ESCPressed() || keyboard.F1Pressed())
        {
            delete help;
            gstate = previous_gstate;
            return 1;
        }
    }
    help->show();
    return 0;
}
bool Game::resultTask(bool inputEnabled)
{
    if(inputEnabled)
    {
        if(keyboard.UpArrowPressed())
            result->moveCursor(Choice::UP);
        if(keyboard.DownArrowPressed())
            result->moveCursor(Choice::DOWN);
        if(keyboard.EnterPressed())
        {
            //wroc do menu
            if(result->getCursorState() == Result::MENU)
            {
                menu = new Menu::Menu;
                delete result;
                gstate = MENU;
                return 1;
            }
            //zakoncz gre
            if(result->getCursorState() == Result::EXIT)
            {
                delete result;
                kill = 1;
                return 1;
            }

        }
        //zakoncz gre
        if(keyboard.ESCPressed())
        {
            delete result;
            kill = 1;
            return 1;
        }
    }
    result->show();
    return 0;
}
bool Game::gameTask(bool inputEnabled)
{
    int res = game->run(keyboard, resetGameTimers);
    if(res == -1 || res == 1)//przegrana/wygrana w grze
    {//pokaz wynik
        delete game;
        result = new Result::Result(res == 1 ? 1 : 0);
        gstate = RESULT;
        return 1;
    }
    if(inputEnabled)
    {
        //potwierdz wyjscie z gry
        if(keyboard.ESCPressed())
        {
            exit = new Exit::Exit();
            previous_gstate = gstate;
            gstate = EXIT;
            resetGameTimers = 1;
            return 1;
        }
        //otworz pomoc
        if(keyboard.F1Pressed())
        {
            help = new Help::Help;
            previous_gstate = gstate;
            gstate = HELP;
            resetGameTimers = 1;
            return 1;
        }
        //zapisz gre
        if(keyboard.F2Pressed())
        {
            game->save();
            resetGameTimers = 1;
            return 1;
        }
        //wczytaj gre
        if(keyboard.F3Pressed())
        {
            std::ifstream f("./save/player.txt");
            if(!f.good())//sprawdz czy save istnieje jesli nie -> nic nie rob
                return 1;
            //w przeciwnym wypadku zakoncz aktualna gre i stworz nowa z save
            delete game;
            clearviewport();
            game = new GameWorld(0,1);
            return 1;
        }
    }

    resetGameTimers = 0;

    return 0;
}
bool Game::menuTask(bool inputEnabled)
{
    if(inputEnabled)
    {
        if(keyboard.UpArrowPressed())
            menu->moveCursor(Choice::UP);
        if(keyboard.DownArrowPressed())
            menu->moveCursor(Choice::DOWN);
        if(keyboard.ESCPressed())
        {
            //potwierdz wyjscie z gry
            delete menu;
            exit = new Exit::Exit;
            previous_gstate = gstate;
            gstate = EXIT;
            return 1;
        }
        if(keyboard.F3Pressed())
        {
            //sprawdz czy save istnieje
            //jesli tak to wczytaj
            std::ifstream f("./save/player.txt");
            if(!f.good())
                return 1;
            delete menu;
            clearviewport();
            gstate = GAME;
            game = new GameWorld(0,1);
            return 1;
        }
        if(keyboard.EnterPressed())
        {
            switch(menu->getCursorState())
            {
                //wybierz poziom trudnosci
            case Menu::START_GAME:
                delete menu;
                difficulty = new Difficulty::Difficulty;
                gstate = DIFFCULTY;
                return 1;
                break;
            case Menu::ABOUT:
                //wyswietl info o grze
                delete menu;
                info = new Info::Info;
                gstate = INFO;
                return 1;
                break;
                //potwierdz wyjscie z gry
            case Menu::EXIT:
                delete menu;
                exit = new Exit::Exit;
                previous_gstate = gstate;
                gstate = EXIT;
                return 1;
                break;
            default:
                break;
            }
        }
    }
    menu->show();
    return 0;
}
bool Game::difficultyTask(bool inputEnabled)
{
    if(inputEnabled)
    {
        if(keyboard.UpArrowPressed())
            difficulty->moveCursor(Choice::UP);
        if(keyboard.DownArrowPressed())
            difficulty->moveCursor(Choice::DOWN);
        if(keyboard.EnterPressed())
        {
            if(difficulty->getCursorState() == Difficulty::EASY)
            {
                //odpal gre na latwa
                delete difficulty;
                game = new GameWorld(0, 0);
                gstate = GAME;
                return 1;
            }
            if(difficulty->getCursorState() == Difficulty::HARD)
            {
                //odpal gre trudna
                delete difficulty;
                game = new GameWorld(1, 0);
                gstate = GAME;
                return 1;
            }
        }
        if(keyboard.ESCPressed())
        {
            //wroc do menu
            delete difficulty;
            menu = new Menu::Menu;
            gstate = MENU;
            return 1;
        }
    }
    difficulty->show();
    return 0;
}
bool Game::exitTask(bool inputEnabled)
{
    if(inputEnabled)
    {
        if(keyboard.UpArrowPressed())
            exit->moveCursor(Choice::UP);
        if(keyboard.DownArrowPressed())
            exit->moveCursor(Choice::DOWN);
        if(keyboard.EnterPressed())
        {
            if(exit->getCursorState() == Exit::YES)
            {
                //zakoncz gre
                if(previous_gstate == GAME)
                    delete game;
                delete exit;
                kill = 1;
                return 1;
            }
            //jesli poprzedni stan to menu
            //wroc do menu
            if(previous_gstate == MENU && exit->getCursorState() == Exit::NO)
            {
                delete exit;
                menu = new Menu::Menu;
                gstate = MENU;
                return 1;
            }
            //jesli poprzedni stan to gra
            //wroc do gry
            if(previous_gstate == GAME && exit->getCursorState() == Exit::NO)
            {
                delete exit;
                gstate = GAME;
                return 1;
            }
        }
        if(keyboard.ESCPressed())
        {
            //wroc do menu
            if(previous_gstate == MENU)
            {
                delete exit;
                menu = new Menu::Menu;
                gstate = MENU;
                return 1;
            }
            //wroc do gry
            else if(previous_gstate == GAME)
            {
                delete exit;
                gstate = GAME;
                return 1;
            }
        }
    }
    exit->show();
    return 0;
}
bool Game::infoTask(bool inputEnabled)
{
    if(inputEnabled)
    {
        if(keyboard.ESCPressed())
        {
            //wroc do menu
            delete info;
            menu = new Menu::Menu;
            gstate = MENU;
            return 1;
        }
    }
    info->show();
    return 0;
}
bool Game::run()
{
    if(kill)//jeœli flaga zakoñczenia programu zostala ustawiona - przerwij pêtlê
        return 0;
    keyboard.event();//pobierz oczekujace zdarzenia z klawiatury

    bool inputEnabled = KEventReady();
    //jezeli cokolwiek zostalo wcisniete wylacz odczyt z klawiatury na 200ms
    if(inputEnabled && keyboard.anythingPressed())
        KEventDelay->start();

    switch(gstate)
    {
    case MENU:
        if(menuTask(inputEnabled))
            return 1;
        break;
    case DIFFCULTY:
        if(difficultyTask(inputEnabled))
            return 1;
        break;
    case GAME:
        if(gameTask(inputEnabled))
            return 1;
        break;
    case INFO:
        if(infoTask(inputEnabled))
            return 1;
        break;
    case HELP:
        if(helpTask(inputEnabled))
            return 1;
        break;
    case EXIT:
        if(exitTask(inputEnabled))
            return 1;
        break;
    case RESULT:
        if(resultTask(inputEnabled))
            return 1;
    default:
        break;
    }
    //podwojne buforowanie
    //dla plynnosci wyswietlanego obrazu
    swapbuffers();
    clearviewport();
    return 1;
}
