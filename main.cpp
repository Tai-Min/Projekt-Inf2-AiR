#include "game.h"

int main() {
    Game *game;//obiekt trzymaj�cy ca�� gr�
    game = new Game();
    while(game->run());//powtarzaj petl� dop�ki gra si� nie zako�czy�a
                       //lub user nie wyda� polecenia zamkni�cia
        delete game;
    return 0;
}
