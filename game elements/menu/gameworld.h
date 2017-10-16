#ifndef __GAMEWORLD_H_INCLUDED__
#define __GAMEWORLD_H_INCLUDED__

#include <graphics.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "../common/kevent.h"
#include "../tiles/gameobject.h"
#include "../tiles/groundtile.h"
#include "../tiles/carttile.h"
#include "../tiles/portal.h"
#include "../tiles/wood.h"
#include "../tiles/coin.h"
#include "../tiles/house1.h"
#include "../tiles/house2.h"
#include "../tiles/house3.h"
#include "../tiles/crate.h"
#include "../tiles/cratestack.h"
#include "../tiles/barrel.h"
#include "../tiles/well.h"
#include "../tiles/lamp.h"
#include "../characters/player.h"
#include "../characters/arrow.h"
#include "../characters/enemy.h"
#include "../common/timer.h"
#include "../common/ganimation.h"

#include "../debug.h"

class GameWorld
{
private:
    struct bg{
        int x;
        int y;
    };

    //flaga sprawdzajaca czy tlo zostalo wczytane
    //aby nie wczytywac go drugi raz
    static bool bgFarLoaded;
    static GImage * bgFarImg;
    const float bgFarParallax = 0.03;
    std::vector<bg> backgroundFar;

    static bool bgMiddleLoaded;
    static GImage * bgMiddleImg;
    const float bgMiddleParallax = 0.1;
    std::vector<bg> backgroundMiddle;

    std::vector<GameObject*> backgroundClose;
    std::vector<GameObject*> coins;
    std::vector<GameObject*> lamps;
    std::vector<GameObject*> portals;
    std::vector<GameObject*> gameObjects;
    std::vector<Arrow*> arrows;
    std::vector<Enemy*> enemies;

    GAnimation *rain;
    Player *player;
    Timer * timer;//liczy czas do przegranej

    //wczytaj odpowiednie rzeczy z odpowiednich plikow
    void loadFar();
    void loadMiddle();
    void loadClose();
    void loadTiles();
    void loadLamps();
    void loadPortals();
    void loadCoins(bool l);
    void loadEnemies(bool l);

    //kontroluje pozostaly czas gry
    void timerTick();

    //ustaw odopowiednie elementy na odpowiednich miejscach
    void decideArrows();
    void decideEnemies(int x, int y, int w, int h);
    void decidePlayer(int x, int y, KEvent & keyboard);

    //posprawdzaj kolizje, animacje i ewentualne flagi i wyswietl obiekty na ekranie
    void renderFar(int x);
    void renderMiddle(int x);
    void renderClose(int x);
    void renderTiles(int x,int y);
    void renderCoins(int x, int y);
    void renderArrows(int x,int y);
    void renderPortals(int x,int y, KEvent & keyboard);
    void renderLamps(int x);
    void renderEnemies(int x, int y);
    void renderUI();

    int minutes = 3;
    int seconds = 59;
    int points = 0;//punkty 20 oznacza wygrana

    bool difficulty;//poziom trudnosci
    bool loadData = 0;//flaga oznaczajaca ze gracz/monety/przeciwnicy powinni zostac wczytani z zapisanego pliku

    //wczytaj gre z zapisanego pliku
    void load(bool & newDiff, int & newX, int & newY, int & newHealth, int & newPoints, int & newMinutes, int & newSeconds);
public:
    GameWorld(bool diff, bool l);
    ~GameWorld();
    int run(KEvent & keyboard, bool reset);
    void save();
};




#endif
