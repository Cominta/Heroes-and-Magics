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

void drawMenuArmy(std::map<heroes::heroesClass, heroes::Attributes> team, int x, bool currentTeam, bool teamSelected, int currentPoint) // false - первая команда, true - вторая
{
    if (currentTeam)
    {
        std::cout << "Second Team: \n";
    }

    else 
    {
        std::cout << "First Team: \n";
    }

    int point = 0;

    for (auto& heroe : team)
    {
        COORD coord = GetConsoleCursorPosition(console);
        coord.X = x;
        SetConsoleCursorPosition(console, coord);

        if (currentPoint == point && teamSelected == currentTeam)
        {
            SetConsoleTextAttribute(console, 9);
        }

        std::cout << heroes::names[heroe.first] << " (" << heroes::findSymbol(heroe.first) << ")\n";
        SetConsoleTextAttribute(console, 15);
        point++;
    }
}

#endif