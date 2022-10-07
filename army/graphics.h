#ifndef ARMY_GRAPHICS_H
#define ARMY_GRAPHICS_H

#include "../heroes.h"
#include "../help.h"

namespace army
{
    namespace graphics
    {
        void drawArmy(std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam);
        void drawFrame();

        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

        void display(std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam)
        {
            std::cout << "\n\t\t\tEdit your`s army\n\n\n\n";

            drawFrame();
            drawArmy(firstTeam, secondTeam);
        }

        std::string findSymbol(heroes::heroesClass find)
        {
            for (auto& heroe : heroes::symbols)
            {
                if (heroe.second == find)
                {
                    return heroe.first;
                }
            }
        }

        void drawTeam(std::map<heroes::heroesClass, heroes::Attributes>& team, int x, int y)
        {
            COORD coord = {x, y};
            SetConsoleCursorPosition(console, coord);

            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = team.begin();

            for (int y = 0; y < 5; y++)
            {
                for (int x = 0; x < 2; x++)
                {
                    std::cout << findSymbol(it->first);
                    it++;
                }

                coord.Y += 1;
                SetConsoleCursorPosition(console, coord);
            }
        }

        void drawArmy(std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam)
        {
            int x = 25;
            int y = 8;

            drawTeam(firstTeam, x, y);
            x = 37;
            drawTeam(secondTeam, x, y);
        }

        void drawFrame()
        {
            std::cout << "\t\t\t";

            int width = 15;
            int height = 10;

            for (int y = 0; y <= height; y++)
            {
                for (int x = 0; x <= width; x++)
                {
                    if (y == 0)
                    {
                        std::cout << "▄";
                    }

                    else if (y == height)
                    {
                        std::cout << "▀";
                    }

                    else if (x == 0 || x == width)
                    {
                        std::cout << "█";
                    }

                    else
                    {
                        std::cout << " ";
                    }
                }

                std::cout << "\n\t\t\t";
            }
        }
    }
}

#endif