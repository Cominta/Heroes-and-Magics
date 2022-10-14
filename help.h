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

void printMap(std::vector<std::vector<std::string>>& map, int width, int height)
{
    std::cout << "\t";

    for (int y = 0; y <= height; y++)
    {
        for (int x = 0; x <= width; x++)
        {
            std::cout << map[y][x];
        }

        std::cout << "\n";

        COORD coord = GetConsoleCursorPosition(console);
        coord.X += 8;
        SetConsoleCursorPosition(console, coord);
    }
}

#endif