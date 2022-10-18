#ifndef MAP_GRAPHICS_H
#define MAP_GRAPHICS_H

#include "../help.h"
#include "logic.h"

namespace map
{
    namespace graphics
    {
        void drawMenu(int x);

        void display(std::vector<std::vector<std::string>>& map, int width, int height)
        {
            std::cout << "\n\t\tEdit your`s army\n\n\n";
            printMap(map, width, height);

            COORD coord = {45, 4};
            SetConsoleCursorPosition(console, coord);

            std::cout << "Objects: \n";

            drawMenu(45);

            coord = {map::logic::xEdit, map::logic::yEdit};
            coord.X += 8;
            coord.Y += 4;
            SetConsoleCursorPosition(console, coord);
        }

        void drawMenu(int x)
        {
            for (int i = 0; i < map::logic::elements.size(); i++)
            {
                COORD coord = GetConsoleCursorPosition(console);
                coord.X = x;
                SetConsoleCursorPosition(console, coord);

                if (i == map::logic::currentPoint)
                {
                    SetConsoleTextAttribute(console, 9);
                }

                std::cout << map::logic::elements[i] << " (" << map::logic::legend[i] << ")\n";

                SetConsoleTextAttribute(console, 15);
            }
        }
    }
}

#endif
