#ifndef BATTLE_GRAPHICS_H
#define BATTLE_GRAPHICS_H

#include "logic.h"
#include <math.h>

namespace battle
{
    namespace graphics
    {   
        enum coloredSide
        {
            LEFT,
            RIGHT,
            UP,
            DOWN
        };

        void coloredDirections(bool clear, battle::logic::Directions direction);
        void colorSide(int range, COORD coord, coloredSide side);
        void setCursor(int x, int y = -1);
        void printUnit(heroes::Attributes attr, int x);
        void printMenu(int x);
        void printHP(int x);
        void coloredTeams(bool team, int color, int exceptionX = -1, int exceptionY = -1);

        std::vector<std::string> menu = {
            "Move",
            "Attack",
            "Show hp"
        };

        bool coloredMoves = false;
        bool coloredAttack = false;

        void display()
        {
            std::cout << "\n\t\tBATTLE!!!\n\n\n";

            short x = 45;
            heroes::Attributes attr = battle::logic::returnCurrentTeam()[battle::logic::currentUnit];

            printMap(battle::logic::map, battle::logic::width, battle::logic::height, attr.x, attr.y);

            coloredTeams(false, 11, attr.x, attr.y);
            coloredTeams(true, 14, attr.x, attr.y);

            if (battle::logic::currentState == battle::logic::States::MENU)
            {
                printUnit(attr, x);
                printMenu(x);
            }

            else if (battle::logic::currentState == battle::logic::States::MOVE_CHOICE)
            {
                coloredDirections(false, battle::logic::currentMoves);
                coloredMoves = true;

                int x = battle::logic::moveX;
                int y = battle::logic::moveY;
                battle::logic::mapToCoordCursor(x, y);
                COORD coord = {x, y};
                SetConsoleCursorPosition(console, coord);
            }

            else if (battle::logic::currentState == battle::logic::States::ATTACK_CHOICE)
            {
                // coloredDirections(false, battle::logic::attack);
            }

            else if (battle::logic::currentState == battle::logic::States::SHOW_HP)
            {
                printHP(x);
            }

            else if (battle::logic::currentState == battle::logic::States::MENU && coloredMoves)
            {
                coloredDirections(true, battle::logic::currentMoves);
                coloredMoves = false;
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

            for (auto unit : teamColor)
            {
                int x = unit.second.x;
                int y = unit.second.y;
                // std::cout << x << " " << y;
                // Sleep(200);

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

        void coloredDirections(bool clear, battle::logic::Directions direction)
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

            int side = 0;
            int* range = &direction.left;
            
            for (int i = 0; i < 4; i++)
            {
                colorSide((*range), coord, (coloredSide)side);
                side++;
                range++;
            }

            SetConsoleTextAttribute(console, 15);
        }

        void colorSide(int range, COORD coord, coloredSide side) 
        {
            for (int i = 0; i < range; i++)
            {
                if (side == coloredSide::LEFT)
                {
                    coord.X--;
                }

                else if (side == coloredSide::RIGHT)
                {
                    coord.X++;
                }

                else if (side == coloredSide::UP)
                {
                    coord.Y--;
                }

                else if (side == coloredSide::DOWN)
                {
                    coord.Y++;
                }

                SetConsoleCursorPosition(console, coord);
                std::cout << " ";
            }
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

        void printHP(int x)
        {
            setCursor(x, 4);
            std::cout << "HP: \n";
            setCursor(x);

            std::map<heroes::heroesClass, heroes::Attributes> team = battle::logic::returnCurrentTeam();

            for (auto unit : team)
            {
                std::cout << heroes::names[unit.first] << " (" << heroes::findSymbol(unit.first) << ")";

                setCursor(x + 20);
                std::cout << "[";

                int percent = ((float)unit.second.health / heroes::attributes[unit.first].health) * 100;

                for (int i = 0; i < round(percent / 10); i++)
                {
                    std::cout << "█";
                }

                for (int i = 0; i < 10 - round(percent / 10); i++)
                {
                    std::cout << "-";
                }

                std::cout << "] " << unit.second.health << "/" << heroes::attributes[unit.first].health <<"\n";
                setCursor(x);
            }
        }
    }
}

#endif 