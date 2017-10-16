#include "gameworld.h"

namespace patch//bug w kompilatorze nie wykrywa std::to_string
               //rozwiazanie znalezione na stackoverflow
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

bool GameWorld::bgFarLoaded = 0;
GImage * GameWorld::bgFarImg = nullptr;

bool GameWorld::bgMiddleLoaded = 0;
GImage * GameWorld::bgMiddleImg = nullptr;

GameWorld::GameWorld(bool diff, bool l)
{
    difficulty = diff;
    loadData = l;//gra powinna zostac zaladowana
    timer = new Timer(1000);
    timer->start();

    std::string anim[4] =
    {
        "./assets/rain/rain1.gif",
        "./assets/rain/rain2.gif",
        "./assets/rain/rain3.gif",
        "./assets/rain/rain4.gif",
    };
    rain = new GAnimation(anim, 4, 800, 750, GImage::IS_TRANSPARENT,60,0);

    //zaladuj wszystkie potrzebne elementy
    loadFar();
    loadMiddle();
    loadClose();
    loadLamps();
    loadTiles();
    loadPortals();
    loadCoins(loadData);
    loadEnemies(loadData);
    Arrow::loadArrows();

    player = new Player();
    if(loadData)
    {
        bool newDiff;
        int newX, newY, newHealth, newPoints, newMinutes, newSeconds;
        //pozyzskaj ogolne informacje o grze
        //i ustaw je
        load(newDiff, newX, newY, newHealth, newPoints, newMinutes, newSeconds);
        player->setY(newY);
        player->setX(newX);
        points = newPoints;
        minutes = newMinutes;
        seconds = newSeconds;
        difficulty = newDiff;
        player->setHealth(newHealth);
        //jesli poziom trudnosci wybrano na TRUDNY
        //zwieksz przedkosc przeciwnikow
        if(difficulty)
        {
            for(int i = 0; i < enemies.size(); i++)
                enemies[i]->setV(0.31);
        }
    }

    //jesli dane nie zostaly zaladowane z zapisu
    //i poziom trudnosci ustawiono na TRUDNY
    //pozmieniaj zasady gry
    if(difficulty && !loadData)
    {
        minutes = 2;
        player->setHealth(5);
        //kazdemu przeciwnikowi dodaj 2 zycia i zwieksz predkosc
        for(int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->addHealth(2);
            enemies[i]->setV(0.31);
        }
    }

    //na wszelki wypadek zeby przeciwnicy nie pospadali za mape przy dlugim ladowaniu
    for(int i = 0; i < enemies.size(); i++)
        enemies[i]->resetTimers();

    if(Debug::debug_enable())
        std::cout << "GameWorld created" << std::endl;
}
GameWorld::~GameWorld()
{
    //skasuj wszystkie wskazniki
    for(int i = 0; i < gameObjects.size(); i++)
        delete gameObjects[i];
    gameObjects.clear();

    for(int i = 0; i < backgroundClose.size(); i++)
        delete backgroundClose[i];
    backgroundClose.clear();

    if(bgFarLoaded)
    {
        bgFarLoaded = 0;
        delete bgFarImg;
    }
    backgroundFar.clear();

    if(bgMiddleLoaded)
    {
        bgMiddleLoaded = 0;
        delete bgMiddleImg;
    }
    backgroundMiddle.clear();

    for(int i = 0; i < lamps.size(); i++)
        delete lamps[i];
    lamps.clear();

    for(int i = 0; i < portals.size(); i++)
        delete portals[i];
    portals.clear();

    for(int i = 0; i < coins.size(); i++)
        delete coins[i];
    coins.clear();

    for(int i = 0; i < arrows.size(); i++)
        delete arrows[i];
    arrows.clear();

    for(int i = 0; i < enemies.size(); i++)
        delete enemies[i];
    enemies.clear();

    Arrow::deleteArrows();
    delete player;
    delete timer;
    delete rain;
    if(Debug::debug_enable())
        std::cout << "GameWorld destroyed" << std::endl;
}

void GameWorld::loadFar()
{
    std::string filename, x, y, width, height;
    std::ifstream file;
    file.open("./level/backgroundFar.txt");
    while(getline(file,filename))
    {
        getline(file, x);
        getline(file, y);
        getline(file, width);
        getline(file, height);
        bg t;
        if(!bgFarLoaded)
        {
            bgFarLoaded = 1;
            bgFarImg = new GImage(filename.c_str(), atoi(width.c_str()), atoi(height.c_str()), GImage::IS_SOLID,0);
        }

        t.x = atoi(x.c_str());
        t.y = atoi(y.c_str());
        backgroundFar.push_back(t);
    }
    file.close();
}
void GameWorld::loadMiddle()
{
    std::string filename, x, y, width, height;
    std::ifstream file;
    file.open("./level/backgroundMiddle.txt");
    while(getline(file,filename))
    {
        getline(file, x);
        getline(file, y);
        getline(file, width);
        getline(file, height);
        bg t;
        if(!bgMiddleLoaded)
        {
            bgMiddleLoaded = 1;
            bgMiddleImg = new GImage(filename.c_str(), atoi(width.c_str()), atoi(height.c_str()), GImage::IS_TRANSPARENT,0);
        }
        t.x = atoi(x.c_str());
        t.y = atoi(y.c_str());
        backgroundMiddle.push_back(t);
    }
    file.close();
}
void GameWorld::loadClose()
{
    std::string type, x, y;
    std::ifstream file;
    file.open("./level/backgroundClose.txt");
    while(getline(file,type))
    {
        getline(file,x);
        getline(file,y);
        switch(type[0])
        {
        case 'A':
            backgroundClose.push_back(new House2(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'B':
            backgroundClose.push_back(new House1(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'C':
            backgroundClose.push_back(new House3(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'D':
            backgroundClose.push_back(new Crate(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'E':
            backgroundClose.push_back(new CrateStack(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'F':
            backgroundClose.push_back(new Barrel(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'G':
            backgroundClose.push_back(new Well(atoi(x.c_str()), atoi(y.c_str())));
            break;
        }
    }
    file.close();
}
void GameWorld::loadTiles()
{
    std::string type, x, y;
    std::ifstream file;
    file.open("./level/gameObjects.txt");
    while(getline(file,type))
    {
        getline(file,x);
        getline(file,y);
        switch(type[0])
        {
        case 'G':
            gameObjects.push_back(new GroundTile(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'C':
            gameObjects.push_back(new CartTile(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'W':
            gameObjects.push_back(new Wood(atoi(x.c_str()), atoi(y.c_str())));
            break;
        case 'Y':
            gameObjects.push_back(new Crate(atoi(x.c_str()), atoi(y.c_str())));
            break;
        }
    }
    file.close();
}
void GameWorld::loadLamps()
{
    std::string x, y;
    std::ifstream file;
    file.open("./level/lamps.txt");
    while(getline(file,x))
    {
        getline(file,x);
        getline(file,y);
        lamps.push_back(new Lamp(atoi(x.c_str()), atoi(y.c_str())));

    }
    file.close();
}
void GameWorld::loadPortals()
{
    std::string x, y, y1;
    std::ifstream file;
    file.open("./level/portals.txt");
    while(getline(file,x))
    {
        getline(file,x);
        getline(file,y);
        getline(file,y1);
        portals.push_back(new Portal(atoi(x.c_str()), atoi(y.c_str()), atoi(y1.c_str())));

    }
    file.close();
}
void GameWorld::loadCoins(bool l)
{
    std::string x, y, name = l ? "./save/coins.txt" : "./level/coins.txt";
    std::ifstream file;
    file.open(name);
    while(getline(file,x))
    {
        getline(file,x);
        getline(file,y);
        coins.push_back(new Coin(atoi(x.c_str()), atoi(y.c_str())));
    }
    file.close();
}
void GameWorld::loadEnemies(bool l)
{
    std::string x, y, h, name = l? "./save/enemies.txt" : "./level/enemies.txt";
    std::ifstream file;
    file.open(name);
    if(name == "./level/enemies.txt")
    {
        while(getline(file,x))
        {
            getline(file,x);
            getline(file,y);
            enemies.push_back(new Enemy(atoi(x.c_str()), atoi(y.c_str())));
        }
    }
    else
    {
        while(getline(file,x))
        {
            getline(file,x);
            getline(file,y);
            getline(file,h);
            enemies.push_back(new Enemy(atoi(x.c_str()), atoi(y.c_str())));
            enemies[enemies.size()-1]->setHealth(atoi(h.c_str()));
        }
    }

    file.close();
}


void GameWorld::timerTick()
{
    if(timer->done())//odliczylo sekunde
    {
        timer->start();//zresetuj timer
        seconds--;//zmniejsz sekundy o 1
        if(seconds < 0)
        {
            seconds = 59;
            minutes--;
        }
    }
}
void GameWorld::decideArrows()
{
    //fizyka strzal
    for(int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->decide();
    }
}
void GameWorld::decideEnemies(int x, int y, int w, int h)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        //jesli przeciwnik nie umiera i jest widoczny
        if(!enemies[i]->dyingb() && enemies[i]->visible())
        {
            enemies[i]->decide();
            if(!enemies[i]->checkCollisions(x,y,w,h, -20))//jak gracz jest w tym zakresie kolizji przeciwnika to zaatakuj gracza
                enemies[i]->checkCollisions(x,y,w,h, 250);//jak gracz jest w tym zakresie kolizji przeciwnika to zacznij go gonic
        }
    }
}
void GameWorld::decidePlayer(int x, int y, KEvent & keyboard)
{
    player->decide(keyboard);
    if(player->shouldSpawnArrow())//sprawdz czy gracz wystrzelil strzale
    {
        //i dodaj obiekt strzaly o odpowiednich parametrach
        if(player->getDirection())
            arrows.push_back(new Arrow(x-20,y,1));
        else
            arrows.push_back(new Arrow(x,y,0));
    }
}


void GameWorld::renderFar(int x)
{
    for(int i = 0; i < backgroundFar.size(); i++)
    {
        if(backgroundFar[i].x - x*bgFarParallax <= 800 && backgroundFar[i].x - x*bgFarParallax + bgFarImg->getWidth() >= 0)
            bgFarImg->show(backgroundFar[i].x - x*bgFarParallax,backgroundFar[i].y);
    }
}
void GameWorld::renderMiddle(int x)
{
    for(int i = 0; i < backgroundMiddle.size(); i++)
    {
        if(backgroundMiddle[i].x - x*bgMiddleParallax<= 800 && backgroundMiddle[i].x - x*bgMiddleParallax + bgMiddleImg->getWidth() >= 0)
            bgMiddleImg->show(backgroundMiddle[i].x - x*bgMiddleParallax,backgroundMiddle[i].y);
    }
}
void GameWorld::renderClose(int x)
{
    for(int i = 0; i < backgroundClose.size(); i++)
        backgroundClose[i]->show(x);
}
void GameWorld::renderTiles(int x, int y)
{
    for(int i = 0; i < gameObjects.size(); i++)
    {
        if(gameObjects[i]->show(x))
        {
            for(int j = 0; j < arrows.size(); j++)              //jesli tile jest na ekranie
            {
                //sprawdz kolizje ze strzalami
                if(arrows[j]->checkCollisions(gameObjects[i]))  //zniszcz strzale jezeli z czyms koliduje
                {
                    //napraw wektor strzal
                    delete arrows[j];
                    for(int k = j; k < arrows.size()-1; k++)
                        arrows[k] = arrows[k+1];
                    arrows.pop_back();
                }
            }
            for(int j = 0; j < enemies.size(); j++) //sprawdz kolizje z przeciwnikami
            {
                enemies[j]->checkCollisions(gameObjects[i]);
            }
            player->checkCollisions(gameObjects[i], x, y, Player::OBJECT);//sprawdz kolizje z graczem
        }

    }
}
void GameWorld::renderCoins(int x, int y)
{
    for(int i = 0; i < coins.size(); i++)
    {
        if(coins[i]->show(x))
        {
            if(player->checkCollisions(coins[i], x, y, Player::COIN) == 3)
            {                                           //jesli gracz koliduje z moneta
                                                        //zniszcz monete
                delete coins[i];                        //napraw wektor z monetami
                for(int j = i; j < coins.size()-1; j++) //i dodaj punkt graczowi
                {
                    coins[j] = coins[j+1];
                }
                coins.pop_back();
                points++;
            }
        }
    }
}
void GameWorld::renderArrows(int x, int y)
{
    for(int i = 0; i < arrows.size(); i++)
    {
        if(!arrows[i]->show(x))//jesli strzala nie jest juz na ekranie
        {
                                //to ja zniszcz
            delete arrows[i];  //i napraw wektor ze strzalami
            for(int j = i; j < arrows.size()-1; j++)
                arrows[j] = arrows[j+1];
            arrows.pop_back();
        }
    }
}
void GameWorld::renderPortals(int x, int y, KEvent & keyboard)
{
    static bool previousUpArr = 0;
    bool upArr = keyboard.UpArrowPressed();
    for(int i = 0; i < portals.size(); i++)
    {
        if(portals[i]->show(x) && upArr && !previousUpArr)//jesli player wcisnal strzalke do gory
        {
            //i koliduje z portalem
            //przenies go w miejsce ktore wskazuje portal
            if(player->checkCollisions(portals[i], x, y, Player::PORTAL) == 2)
            {
                player->setY(static_cast<Portal*>(portals[i])->getPortalY());
                break;
            }
        }
    }
    previousUpArr = upArr;
}
void GameWorld::renderLamps(int x)
{
    for(int i = 0; i < lamps.size(); i++)
        lamps[i]->show(x);
}
void GameWorld::renderEnemies(int x, int y)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        if(!enemies[i]->alive())//jak przeciwnik zakonczyl animacje umierania
        {
            //zniszcz go i napraw wektor z przeciwnikami
            delete enemies[i];
            for(int j = i; j < enemies.size()-1; j++)
                enemies[j] = enemies[j+1];
            enemies.pop_back();
        }
        else if(enemies[i]->dyingb())//jesli przeciwnik umiera to nadal go pokazuj
        {                           //niezaleznie od tego czy jest na ekranie
            enemies[i]->show(x);    //aby dokonczy animacje umierania
        }
        else if(enemies[i]->show(x) && !enemies[i]->dyingb())//jak jest na ekranie i nie jest w trakcie umierania
        {
            for(int j  = 0; j < arrows.size(); j++)         //sprawdz czy koliduje ze strzalami
            {
                //jesli tak to zadaj mu obrazenia zniszcz strzale i napraw wektor ze strzalami
                if(arrows[j]->checkCollisions(enemies[i]))
                {
                    delete arrows[j];
                    for(int k = j; k < arrows.size()-1; k++)
                        arrows[k] = arrows[k+1];
                    arrows.pop_back();
                    enemies[i]->addHealth(-1);
                }
            }
            if(enemies[i]->damagePlayer())//jesli przeciwnik zadal graczowni obrazenia
                player->addHealth(-1);    //zmniejsz punkty zycia gracza o 1
            player->checkCollisions(enemies[i], x, y);//sprawdz kolizje gracza z przeciwnikami
        }
        else//jesli przeciwnik nie umiera i nie jest na ekranie
        {
            enemies[i]->resetTimers();//zresetuj timery odpowiedzialne za fizyke przeciwnikow
        }
    }
}
void GameWorld::renderUI()
{
    setcolor(WHITE);
    std::string t = patch::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + patch::to_string(seconds);
    outtextxy(70,20,(char*)t.c_str());
    t = "MONETY: ";
    t += (points < 10 ? "0" : "") + patch::to_string(points);
    outtextxy(80,55,(char*)t.c_str());
    t = "ZYCIA: ";
    t+= patch::to_string(player->getHealth());
    outtextxy(700,55,(char*)t.c_str());
}
void GameWorld::load(bool & newDiff, int & newX, int & newY, int & newHealth, int & newPoints, int & newMinutes, int & newSeconds)
{
    std::string t;
    std::ifstream file;
    file.open("./save/player.txt");
    getline(file, t);
    newX = atoi(t.c_str());
    getline(file, t);
    newY = atoi(t.c_str());
    getline(file, t);
    newHealth = atoi(t.c_str());
    getline(file, t);
    newPoints = atoi(t.c_str());
    getline(file, t);
    newMinutes = atoi(t.c_str());
    getline(file, t);
    newSeconds = atoi(t.c_str());
    getline(file, t);
    newDiff = atoi(t.c_str());
    file.close();
}


int GameWorld::run(KEvent & keyboard, bool reset)
{
    if(reset)//reset jest true tylko po powrocie z panelu wyjscie/pomoc
    {
        //aby nie popsula sie fizyka postaci
        player->resetTimers();
        timer->start();
        for(int i = 0; i < enemies.size(); i++)
            enemies[i]->resetTimers();
    }

    timerTick();

    int x,y;
    player->getPos(x,y);
    //std::cout << x+300 << std::endl;
    decideEnemies(x,y,player->getH(), player->getW());
    decideArrows();
    decidePlayer(x,y, keyboard);

    renderFar(x);
    renderMiddle(x);
    renderClose(x);
    renderTiles(x,y);
    renderPortals(x, y, keyboard);
    renderEnemies(x, y);
    renderCoins(x, y);
    renderArrows(x,y);
    player->show();
    renderLamps(x);
    rain->animate(0,0,0);
    renderUI();

    if(minutes <= -1 && seconds <= 59 || player->died())//czas sie skonczyl lub gracz umarl
        return -1;                                      //zwroc przegrana
    if(points == 20)//wszystkie monety zebrane
        return 1;   //zwroc wygrana
    return 0;
}
void GameWorld::save()
{
    std::fstream file;
    file.open("./save/enemies.txt", std::fstream::out | std::ofstream::trunc);
    for(int i = 0; i < enemies.size(); i++)
    {
        file << "E\n";
        file << enemies[i]->getX();
        file << "\n";
        file << enemies[i]->getY();
        file << "\n";
        file << enemies[i]->getHealth();
        if(i < enemies.size()-1)
            file << "\n";
    }
    file.close();
    file.open("./save/coins.txt", std::fstream::out | std::ofstream::trunc);
    for(int i = 0; i < coins.size(); i++)
    {
        file << "C\n";
        file << static_cast<Coin*>(coins[i])->getX();
        file << "\n";
        file << static_cast<Coin*>(coins[i])->getY();
        if(i < coins.size()-1)
            file << "\n";
    }
    file.close();
    file.open("./save/player.txt", std::fstream::out | std::ofstream::trunc);
    file << player->getX();
    file << "\n";
    file << player->getY();
    file << "\n";
    file << player->getHealth();
    file << "\n";
    file << points;
    file << "\n";
    file << minutes;
    file << "\n";
    file << seconds;
    file << "\n";
    file << difficulty;
    file.close();
}
