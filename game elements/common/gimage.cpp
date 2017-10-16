#include "gimage.h"

//przerobiona funkcja z kodu zrodlowego winbgim
//wspiera transparentnosc w ludzki sposob
void betterputimage( int left, int top, void *bitmap)
{
    long width, height;   // Width and height of the image in pixels
    WindowData* pWndData; // Our own window data struct for active window
    HDC hDC;              // Device context for the active window
    HDC hMemoryDC;        // Memory device context for a copy of the image
    HBITMAP hOldBitmap;   // Handle to original bitmap of hMemDC
    HBITMAP hBitmap;      // Handle to bitmap that will be selected into hMemDC
    BITMAP* pUser;        // A pointer into the user's buffer, used as a BITMAP

    // Preliminary computations
    pUser = (BITMAP*) bitmap;
    width = pUser->bmWidth;
    height = pUser->bmHeight;
    pWndData = BGI__GetWindowDataPtr( );
    hDC = BGI__GetWinbgiDC( );



    // Create the memory DC and select a new larger bitmap for it, saving the
    // original bitmap to restore later (before deleting).
    hMemoryDC = CreateCompatibleDC(hDC);
    hBitmap = CreateCompatibleBitmap(hDC, pUser->bmWidth, pUser->bmHeight);
    hOldBitmap = (HBITMAP) SelectObject(hMemoryDC, hBitmap);

    // Grab the bitmap data from the user's bitmap and put it in hMemoryDC
    SetBitmapBits(hBitmap, pUser->bmHeight*pUser->bmWidthBytes, pUser->bmBits);

    // Copy the bitmap from hMemoryDC to the active hDC:
    TransparentBlt(hDC, left, top, width, height, hMemoryDC, 0, 0, width,height, COLOR(0,0,0));
    //cont(left,top,&hBitmap,mirror);
    RefreshWindow( NULL );

    // Delete resources
    BGI__ReleaseWinbgiDC( );
    SelectObject(hMemoryDC, hOldBitmap); // Restore original bmp so it's deleted
    DeleteObject(hBitmap);               // Delete the bitmap we used
    DeleteDC(hMemoryDC);                 // Delete the memory dc and it's bmp
}

GImage::GImage(std::string name_, int width_, int height_, IMAGETYPE type_, bool addmirror)
{
    width = width_;
    height = height_;
    name = name_;
    type = type_;
    bitmap = new char[imgsize = imagesize(0,0,width,height)];//stworz tablice o odpowiedniej wielkosci
    readimagefile(name.c_str(), 0,0, width,height);//wczytaj obrazek z dysku
    getimage(0,0,width,height, bitmap);//zlap wyswietlany obrazek do bitmapy
    clearviewport();//wyczysc ekran w celu wczytania innego obrazka
    if(addmirror)//jesli addmirror jest true - wczytaj plik z odbitym wertykalnie obrazkiem
    {
        mirrored = 1;
        std::string mirrName = name_.substr(0,name_.length()-4);
        mirrName+="Mirr.gif";
        bitmapMirrored = new char[imgsize = imagesize(0,0,width,height)];
        readimagefile(mirrName.c_str(), 0,0, width,height);
        getimage(0,0,width,height, bitmapMirrored);
        clearviewport();
    }

    if(imgsize == -1)//w przypadku za duzego obrazka
    {
        if(Debug::debug_enable())
            std::cout << "Image: " << name << " is too large" << std::endl;
    }
    if(Debug::debug_enable())
        std::cout << "Image " << name << " created, size: " << imgsize << " bytes" << std::endl;
}
GImage::~GImage()
{
    delete[] bitmap;
    if(mirrored)
    {
        mirrored = 0;
        delete[] bitmapMirrored;
    }
    if(Debug::debug_enable())
        std::cout << "Image " << name << " destroyed" << std::endl;
}


int GImage::getWidth()
{
    return width;
}

void GImage::show(int x, int y)
{
    if(type == IS_SOLID)
    {
        if(justify == TOP_LEFT)//pivot w lewym gornym rogu
            putimage(x,y,bitmap,COPY_PUT);
        if(justify == CENTER_CENTER)//pivot na srodku
            putimage(x-width/2,y-height/2,bitmap,COPY_PUT);
    }
    else if(type == IS_TRANSPARENT)
    {
        if(justify == TOP_LEFT)
            betterputimage(x,y,bitmap);
        if(justify == CENTER_CENTER)
            betterputimage(x-width/2,y-height/2,bitmap);
    }
}
void GImage::showMirrored(int x, int y)
{
    /*int t1 = width;
    int t2 = 0;
    for(int i = 8; i < imgsize; i+=4)
    {
        if(!(bitmap[i+2] == 0 && bitmap[i+1] == 0 && bitmap[i] == 0))
        {
            if(justify == TOP_LEFT)
                putpixel(x+t1, y+t2,COLOR(bitmap[i+2],bitmap[i+1],bitmap[i]));
            if(justify == CENTER_CENTER)
                putpixel(x+t1-width/2, y+t2-height/2,COLOR(bitmap[i+2],bitmap[i+1],bitmap[i]));
        }

        t1--;
        if(t1 < 0)
        {
            t2++;
            t1 = width;
        }
    }*/

    if(justify == TOP_LEFT)
        betterputimage(x,y,bitmapMirrored);
    if(justify == CENTER_CENTER)
        betterputimage(x-width/2,y-height/2,bitmapMirrored);
}
void GImage::setJustify(JUSTIFY jus)
{
    justify = jus;
}


