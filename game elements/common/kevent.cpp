#include "kevent.h"

void KEvent::clearPresses()
{
    keys.F1 = 0;
    keys.F2 = 0;
    keys.F3 = 0;
    keys.Spacebar = 0;
    keys.RightArrow = 0;
    keys.LeftArrow = 0;
    keys.UpArrow = 0;
    keys.DownArrow = 0;
    keys.ESC = 0;
    keys.Enter = 0;
}


bool KEvent::F1Pressed()
{
    return keys.F1;
}
bool KEvent::F2Pressed()
{
    return keys.F2;
}
bool KEvent::F3Pressed()
{
    return keys.F3;
}
bool KEvent::SpacebarPressed()
{
    return keys.Spacebar;
}
bool KEvent::RightArrowPressed()
{
    return keys.RightArrow;
}
bool KEvent::LeftArrowPressed()
{
    return keys.LeftArrow;
}
bool KEvent::UpArrowPressed()
{
    return keys.UpArrow;
}
bool KEvent::DownArrowPressed()
{
    return keys.DownArrow;
}
bool KEvent::ESCPressed()
{
    return keys.ESC;
}
bool KEvent::EnterPressed()
{
    return keys.Enter;
}
bool KEvent::anythingPressed()
{
    return wasPressed;
}
void KEvent::event()
{
    wasPressed = 0;
    clearPresses();
    //bitowe AND z 0x8000 zwraca czy odpowiedni klawisz jest wcisniety
    wasPressed += keys.F1 = GetKeyState(VK_F1) & 0x8000;
    wasPressed += keys.F2 = GetKeyState(VK_F2) & 0x8000;
    wasPressed += keys.F3 = GetKeyState(VK_F3) & 0x8000;
    wasPressed += keys.Spacebar = GetKeyState(VK_SPACE) & 0x8000;
    wasPressed += keys.RightArrow = GetKeyState(VK_RIGHT) & 0x8000;
    wasPressed += keys.LeftArrow = GetKeyState(VK_LEFT) & 0x8000;
    wasPressed += keys.UpArrow = GetKeyState(VK_UP) & 0x8000;
    wasPressed += keys.DownArrow = GetKeyState(VK_DOWN) & 0x8000;
    wasPressed += keys.ESC = GetKeyState(VK_ESCAPE) & 0x8000;
    wasPressed += keys.Enter = GetKeyState(VK_RETURN) & 0x8000;
    /*while(kbhit())//tragedia
    {
        char c = getch();
        if(!c)
        {
            c = getch();
            switch(c)
            {
            case KEY_F1:
                keys.F1 = 1;
                break;
            case KEY_UP:
                keys.UpArrow = 1;
                break;
            case KEY_DOWN:
                keys.DownArrow = 1;
                break;
            default:
                break;
            }
        }
        else
        {
            switch(c)
            {
            case KEY_SPACEBAR:
                keys.Spacebar = 1;
                break;
            case KEY_ESC:
                keys.ESC = 1;
                break;
            case KEY_ENTER:
                keys.Enter = 1;
                break;
            default:
                break;
            }
        }
    }*/
}
