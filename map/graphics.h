#ifndef MAP_GRAPHICS_H
#define MAP_GRAPHICS_H

#include "../help.h"

namespace map
{
    namespace graphics
    {
        void display(std::vector<std::vector<std::string>>& map, int width, int height)
        {
            std::cout << "\n\t\tEdit map:\n\n\n";
            printMap(map, width, height);
        }
    }
}

#endif