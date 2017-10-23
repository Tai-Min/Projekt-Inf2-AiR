#include "game.h"

int main() {
    Game *game;//obiekt trzymaj¹cy ca³¹ grê
    game = new Game();
    while(game->run());//powtarzaj petlê dopóki gra siê nie zakoñczy³a
                       //lub user nie wyda³ polecenia zamkniêcia
        delete game;
    return 0;
}
