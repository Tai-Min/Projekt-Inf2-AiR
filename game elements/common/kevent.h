#ifndef __KEVENT_H_INCLUDED__
#define __KEVENT_H_INCLUDED__

#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACEBAR 32
#include <graphics.h>
#include <windows.h>

class KEvent
{
private:
    struct KeysPressed{
        bool F1 = 0;
        bool F2 = 0;
        bool F3 = 0;
        bool Spacebar = 0;
        bool RightArrow = 0;
        bool LeftArrow = 0;
        bool UpArrow = 0;
        bool DownArrow = 0;
        bool ESC = 0;
        bool Enter = 0;
    } keys;

    bool wasPressed = 0;
    void clearPresses();

public:
    bool F1Pressed();
    bool F2Pressed();
    bool F3Pressed();
    bool SpacebarPressed();
    bool RightArrowPressed();
    bool LeftArrowPressed();
    bool UpArrowPressed();
    bool DownArrowPressed();
    bool ESCPressed();
    bool EnterPressed();
    bool anythingPressed();

    void event();
};

#endif
