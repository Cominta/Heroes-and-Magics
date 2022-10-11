#ifndef HELP_H
#define HELP_H

#include <Windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) // без понятия что тут твориться, с инета кусок
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;

    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }

    else
    {
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

enum KeyCode 
{ 
    ENTER = 13, 
    ESCAPE = 27, 
    SPACE = 32, 
    LEFT = 75, 
    RIGHT = 77, 
    UP = 72, 
    DOWN = 80 
};

#endif