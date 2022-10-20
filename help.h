#ifndef HELP_H
#define HELP_H

#include <Windows.h>
#include "heroes.h"

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

void printMap(std::vector<std::vector<std::string>>& map, int width, int height, int xColor = -1, int yColor = -1)
{
    std::cout << "\t";

    for (int y = 0; y <= height; y++)
    {
        for (int x = 0; x <= width; x++)
        {
            if (x == xColor && y == yColor)
            {
                SetConsoleTextAttribute(console, 9);
            }

            std::cout << map[y][x];
            SetConsoleTextAttribute(console, 15);
        }

        std::cout << "\n";

        COORD coord = GetConsoleCursorPosition(console);
        coord.X += 8;
        SetConsoleCursorPosition(console, coord);
    }
}

void checkPoint(int& point, int keyCode, int max)
{
    if (keyCode == KeyCode::UP)
    {
        point--;

        if (point < 0)
        {
            point = max;
        }
    }

    else if (keyCode == KeyCode::DOWN)
    {
        point++;

        if (point > max)
        {
            point = 0;
        }
    }
}

#endif