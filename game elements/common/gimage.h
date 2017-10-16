#ifndef __GIMAGE_H_INCLUDED__
#define __GIMAGE_H_INCLUDED__

#define WINVER 0x0501//win xp
#include <graphics.h>
#include <string>
#include <windows.h>
#include "winbgitypes.h"

#include "../debug.h"

class GImage
{
public:
    enum IMAGETYPE{//typy obrazka
        IS_SOLID = 0,//po zmianie funkcji wyswietlajacej transparentne obrazki
        IS_TRANSPARENT = 1//enum w sumie jest nieaktualny
    };
    enum JUSTIFY{//mozliwe justowania obrazka
        TOP_LEFT = 0,
        CENTER_CENTER = 1
    } justify = TOP_LEFT;

    GImage(std::string name, int width, int height, IMAGETYPE type_, bool addmirror);
    ~GImage();

    int getWidth();//zwroc szerokosc obrazka

    void show(int x, int y);//pokaz obrazek
    void showMirrored(int x, int y);//pokaz obrazek odbity wertykalnie
    void setJustify(JUSTIFY jus);//ustaw justowanie

private:
    IMAGETYPE type;

    std::string name;//sciezka do obrazka

    int imgsize = 0;//wielkosc obrazka w bajtach wyliczana przez winbgim
    int width,height;

    char *bitmap;//tablica trzymajaca obrazek w pamieci
    char *bitmapMirrored;//tablica trzymajaca odbity obrazek w pamieci

    bool mirrored = 0;//true oznacza ze obiekt ma wczytac obrazek i jego odbicie
};                    //w przeciwnym wypadku nie wczytuj odbicia




#endif
