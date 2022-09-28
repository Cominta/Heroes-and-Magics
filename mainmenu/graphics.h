#ifndef MAIN_MENU_GRAPHICS_H
#define MAIN_MENU_GRAPHICS_H

#include <iostream>
#include <vector>

#include "logic.h"

namespace mainmenu
{
    namespace graphics 
    {
        void drawName();
        void drawMenu();

        std::vector<std::string> menu = {
            "Play",
            "Shop",
            "Army",
            "Exit"
        };

        void display()
        {
            system("cls");

            mainmenu::graphics::drawName();
            mainmenu::graphics::drawMenu();
        }

        void drawName()
        {
            std::cout << "\n";
            std::cout << "\t  *   *   *****   *****     ***     *****   ****     \n";
            std::cout << "\t  *   *   *       *   *    *   *    *       *   *    \n";
            std::cout << "\t  *   *   *       *   *   *     *   *       *        \n";
            std::cout << "\t  *****   *****   *****   *     *   *****   ****     \n";
            std::cout << "\t  *   *   *       * *     *     *   *           *    \n";
            std::cout << "\t  *   *   *       *  *     *   *    *       *   *    \n";
            std::cout << "\t  *   *   *****   *   *     ***     *****    ****    \n";

            std::cout << "\n";

            std::cout << "\t              *      *     *   ****                  \n";
            std::cout << "\t             * *     **    *   *   *                 \n";
            std::cout << "\t             * *     * *   *   *   *                 \n";
            std::cout << "\t            *   *    *  *  *   *   *                 \n";
            std::cout << "\t            *****    *   * *   *   *                 \n";
            std::cout << "\t           *     *   *    **   *   *                 \n";
            std::cout << "\t           *     *   *     *   ****                  \n";

            std::cout << "\n";

            std::cout << "\t *       *      *      *****   *****    ****   ****  \n";
            std::cout << "\t * *   * *     * *     *   *   *****   *       *   * \n";
            std::cout << "\t *  * *  *     * *     *               *       *     \n";
            std::cout << "\t *   *   *    *   *    * ***   *****   *       ****  \n";
            std::cout << "\t *       *    *****    *   *   *****   *           * \n";
            std::cout << "\t *       *   *     *   *   *   *****   *       *   * \n";
            std::cout << "\t *       *   *     *   *****   *****    ****    **** \n";

            std::cout << "\n";
        }

        void drawMenu()
        {
            std::cout << "\n";

            for (int i = 0; i < menu.size(); i++)
            {
                std::cout << "\t\t\t\t" << menu[i];

                if (mainmenu::logic::currentPoint == i)
                {
                    std::cout << " <-- ";
                }

                std::cout << "\n";
            }
        }
    }
}

#endif