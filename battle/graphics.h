#ifndef BATTLE_GRAPHICS_H
#define BATTLE_GRAPHICS_H

#include "logic.h"

namespace battle
{
    namespace graphics
    {   
        void coloredMoves(bool clear);
        void setCursor(int x, int y = -1);
        void printUnit(heroes::Attributes attr, int x);
        void printMenu(int x);
        void coloredTeams(bool team, int color, int exceptionX = -1, int exceptionY = -1);

        std::vector<std::string> menu = {
            "Move",
            "Attack"
        };

        bool colored = false;

        void display()
        {
            std::cout << "\n\t\tBATTLE!!!\n\n\n";

            short x = 45;
            heroes::Attributes attr = battle::logic::returnCurrentTeam()[battle::logic::currentUnit];

            printMap(battle::logic::map, battle::logic::width, battle::logic::height, attr.x, attr.y);

            if (battle::logic::move)
            {
                coloredMoves(false);
                colored = true;
            }

            else if (!battle::logic::move && colored)
            {
                coloredMoves(true);
                colored = false;
            }

            coloredTeams(false, 11, attr.x, attr.y);
            coloredTeams(true, 14, attr.x, attr.y);
            printUnit(attr, x);
            printMenu(x);

            if (battle::logic::move)
            {
                coloredMoves(false);

                int x = battle::logic::moveX;
                int y = battle::logic::moveY;
                battle::logic::mapToCoordCursor(x, y);
                COORD coord = {x, y};
                SetConsoleCursorPosition(console, coord);
            }
        }

        void setCursor(int x, int y)
        {
            COORD coord = {x, y};

            if (y == -1)
            {
                coord.Y = GetConsoleCursorPosition(console).Y;
            }

            SetConsoleCursorPosition(console, coord);
        }

        void coloredTeams(bool team, int color, int exceptionX, int exceptionY)
        {
            std::map<heroes::heroesClass, heroes::Attributes> teamColor;

            if (team)
            {
                teamColor = battle::logic::secondTeam;
            }

            else 
            {
                teamColor = battle::logic::firstTeam;
            }

            SetConsoleTextAttribute(console, color);

            for (auto& unit : teamColor)
            {
                int x = unit.second.x;
                int y = unit.second.y;

                if (x == exceptionX && y == exceptionY)
                {
                    continue;
                }

                battle::logic::mapToCoordCursor(x, y);

                SetConsoleCursorPosition(console, {(short)x, (short)y});
                std::cout << heroes::findSymbol(unit.first);
            }

            SetConsoleTextAttribute(console, 15);
        }

        void coloredMoves(bool clear)
        {
            int xUnit = battle::logic::returnCurrentTeam()[battle::logic::currentUnit].x;
            int yUnit = battle::logic::returnCurrentTeam()[battle::logic::currentUnit].y;

            battle::logic::mapToCoordCursor(xUnit, yUnit);

            COORD coord = {xUnit, yUnit};
            SetConsoleCursorPosition(console, coord);

            if (clear)
            {
                SetConsoleTextAttribute(console, 15);
            }

            else 
            {
                SetConsoleTextAttribute(console, 42);
            }

            // оптимизировать блять
            for (int i = 0; i < battle::logic::currentMoves.right; i++)
            {
                coord.X++;
                SetConsoleCursorPosition(console, coord);
                std::cout << " ";
            }

            coord.X = xUnit;

            for (int i = 0; i < battle::logic::currentMoves.left; i++)
            {
                coord.X--;
                SetConsoleCursorPosition(console, coord);
                std::cout << " ";
            }

            coord.X = xUnit;

            for (int i = 0; i < battle::logic::currentMoves.up; i++)
            {
                coord.Y--;
                SetConsoleCursorPosition(console, coord);
                std::cout << " ";
            }

            coord.Y = yUnit;

            for (int i = 0; i < battle::logic::currentMoves.down; i++)
            {
                coord.Y++;
                SetConsoleCursorPosition(console, coord);
                std::cout << " ";
            }

            coord.Y = yUnit;

            SetConsoleTextAttribute(console, 15);
        }

        void printUnit(heroes::Attributes attr, int x)
        {
            short y = 4;

            setCursor(x, y);

            std::cout << "Current turn: ";

            if (battle::logic::currentTeam)
            {
                std::cout << "second team\n";
            }

            else 
            {
                std::cout << "first team\n";
            }

            setCursor(x);

            std::cout << "Current unit: ";
            std::cout << heroes::names[battle::logic::currentUnit] << " (" << heroes::findSymbol(battle::logic::currentUnit) << ")\n\n"; 
            setCursor(x);
            std::cout << "Attributes: ";
            std::cout << "hp = " << attr.health << ", armor = " << attr.armor << "\n";
            setCursor(x);
            std::cout << "attack near (min) = " << attr.attackNearMin << ", attack long (min) = " << attr.attackLongMin << "\n";
            setCursor(x);
            std::cout << "speed = " << attr.speed << "\n";
        }

        void printMenu(int x)
        {
            std::cout << "\n";
            setCursor(x);
            std::cout << "What do you want to do?\n";
            setCursor(x);
            
            for (int i = 0; i < menu.size(); i++)
            {
                if (i == battle::logic::currentPointMenu)
                {
                    SetConsoleTextAttribute(console, 9);
                }

                std::cout << i + 1 << ". " << menu[i] << "\n";
                SetConsoleTextAttribute(console, 15);
                setCursor(x);
            }
        }
    }
}

#endif 