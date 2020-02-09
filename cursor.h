#ifndef CURSOR_H
#define CURSOR_H
#include <windows.h>

class Cursor{
private:
    HANDLE hcon;
    COORD pos;
public:
    Cursor(){


    void reiniciarPos(){
        hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        pos.X = 1;
        pos.Y = 1;
    }
};

#endif // CURSOR_H
