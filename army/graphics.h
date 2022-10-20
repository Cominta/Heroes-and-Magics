#ifndef ARMY_GRAPHICS_H
#define ARMY_GRAPHICS_H

#include "../heroes.h"
#include "../help.h"
#include "../map/logic.h"
#include "logic.h"

namespace army
{
    namespace graphics
    {
        void drawEditUnit(std::map<heroes::heroesClass, heroes::Attributes> team, int x);
        void drawMenuArmy(std::map<heroes::heroesClass, heroes::Attributes> team, int x, bool currentTeam);

        bool editUnit = false;

        void display(std::vector<std::vector<std::string>>& map, std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam, int width, int height)
        {
            std::cout << "\n\t\tEdit your`s army\n\n\n";

            printMap(map, width, height);

            short x = 45;
            short y = 4;

            COORD coord = {x, y};
            SetConsoleCursorPosition(console, coord);
            drawMenuArmy(firstTeam, x, false);

            x = 65;
            coord = {x, y};
            SetConsoleCursorPosition(console, coord);
            drawMenuArmy(secondTeam, x, true);

            if (army::logic::editUnit)
            {
                x = 85;
                coord = {x, y};
                SetConsoleCursorPosition(console, coord);

                if (army::logic::currentTeam)
                {
                    drawEditUnit(secondTeam, x);
                }

                else 
                {
                    drawEditUnit(firstTeam, x);
                }
            }
        }

        void drawMenuArmy(std::map<heroes::heroesClass, heroes::Attributes> team, int x, bool currentTeam) // false - первая команда, true - вторая
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

                if (army::logic::currentPoint == point && army::logic::currentTeam == currentTeam)
                {
                    SetConsoleTextAttribute(console, 9);
                }

                std::cout << heroes::names[heroe.first] << " (" << heroes::findSymbol(heroe.first) << ")\n";
                SetConsoleTextAttribute(console, 15);
                point++;
            }
        }

        void drawEditUnit(std::map<heroes::heroesClass, heroes::Attributes> team, int x)
        {
            std::cout << "Edit unit: \n";

            std::vector<heroes::heroesClass> toPrint = army::logic::checkUnitsPrint(team);
            
            for (int i = 0; i < toPrint.size(); i++)
            {
                if (i == army::logic::currentPointEdit)
                {
                    SetConsoleTextAttribute(console, 9);
                }

                COORD coord = GetConsoleCursorPosition(console);
                coord.X = x;
                SetConsoleCursorPosition(console, coord);
                std::cout << heroes::names[toPrint[i]] << " (" << heroes::findSymbol(toPrint[i]) << ")\n";
                SetConsoleTextAttribute(console, 15);
            }
        }
    }
}

#endif