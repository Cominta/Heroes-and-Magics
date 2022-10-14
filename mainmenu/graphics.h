#ifndef MAIN_MENU_GRAPHICS_H
#define MAIN_MENU_GRAPHICS_H

#include <iostream>
#include <vector>
#include <Windows.h>

#include "logic.h"
#include "../help.h"

namespace mainmenu
{
    namespace graphics 
    {
        void drawName();
        void drawLetter(char symbol, int coordX);
        void drawMenu();        

        std::vector<std::string> menu = {
            "██▓███   ██▓    ▄▄▄     ▓██   ██▓\n\t\t\t     ██░  ██▒▓██▒   ▒████▄    ▒██  ██▒\n\t\t\t     ██░ ██▓▒▒██░   ▒██  ▀█▄   ▒██ ██░\n\t\t\t     ██▄█▓▒ ▒▒██░   ░██▄▄▄▄██  ░ ▐██▓░\n\t\t\t     ██▒ ░  ░░██████▒▓█   ▓██▒ ░ ██▒▓░\n\t\t\t     ▓▒░ ░  ░░ ▒░▓  ░▒▒   ▓▒█░  ██▒▒▒\n\t\t\t     ▒ ░     ░ ░ ▒  ░ ▒   ▒▒ ░▓██ ░▒░",
            "▄▄▄       ██▀███   ███▄ ▄███  ██   ██▓\n\t\t\t     ████▄    ▓██ ▒ ██  ██▒▀█▀ ██▒ ▒██  ██▒\n\t\t\t     ██  ▀█▄  ▓██ ░▄█ ▒▓██    ▓██░  ▒██ ██░\n\t\t\t     ██▄▄▄▄██ ▒██▀▀█▄  ▒██    ▒██   ░ ▐██▓░\n\t\t\t     █    ▓██▒░██▓ ██▒▒ ██▒   ░██▒   ██▒▓░\n\t\t\t     ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ▒░   ░  ░  ██▒▒▒\n\t\t\t     ▒   ▒▒ ░  ░▒ ░ ▒░░  ░      ░ ▓██ ░▒░\n\t\t\t     ░   ▒     ░░   ░ ░      ░    ▒ ▒ ░░",
            " ███▄ ▄███▓ ▄▄▄       ██▓███  \n\t\t\t     ▓██▒▀█▀ ██▒▒████▄    ▓██░  ██▒\n\t\t\t     ▓██    ▓██░▒██  ▀█▄  ▓██░ ██▓▒\n\t\t\t     ▓██    ▓██░▒██  ▀█▄  ▓██░ ██▓▒\n\t\t\t     ▒██    ▒██ ░██▄▄▄▄██ ▒██▄█▓▒ ▒\n\t\t\t     ▒██▒   ░██▒ ▓█   ▓██▒▒██▒ ░  ░\n\t\t\t     ░ ▒░   ░  ░ ▒▒   ▓▒█░▒▓▒░ ░  ░\n\t\t\t     ░  ░      ░  ▒   ▒▒ ░░▒ ░\n\t\t\t     ░      ░     ░   ▒   ░░",
            "▓█████ ▒██   ██▒ ██  ███████\n\t\t\t     ▓█   ▀ ▒▒ █ █ ▒░▓██▒▓  ██▒ ▓▒\n\t\t\t     ▒███   ░░  █   ░▒██▒▒  ██░ ▒░\n\t\t\t     ▒██  ▄  ░ █ █ ▒ ░██░░ ▓██▓ ░ \n\t\t\t     ░█████▒▒██▒ ▒██▒░██░  ▒██▒ ░ \n\t\t\t     ░░ ▒░ ░▒▒ ░ ░▓ ░░▓    ▒ ░░ "
        };
        std::string name = "heroes and magics";
        bool firstTime = true;

        void display()
        {
            system("cls");

            drawName();
            drawMenu();
        }        

        void drawName()
        {
            bool tab = true;
            for (int i = 0; i < name.size(); i++)
            {
                if (firstTime)
                {
                    Sleep(100);
                }

                COORD coord = GetConsoleCursorPosition(console);

                if (name[i] != ' ')
                {
                    coord.Y -= 7;
                    SetConsoleCursorPosition(console, coord);
                }

                else 
                {
                    coord.Y += 9;

                    if (tab)
                    {
                        coord.X = 25;
                        tab = false;
                    }

                    else 
                    {
                        coord.X = 0;
                    }

                    SetConsoleCursorPosition(console, coord);
                }

                drawLetter(name[i], coord.X);
            }

            firstTime = false;
        }

        void drawLetter(char symbol, int coordX)
        {
            std::vector<std::string> letter;
            if (symbol == 'h')
            {
                letter = {
                    "     ▄█    █▄     \n",
                    "    ███    ███    \n",
                    "    ███    ███    \n",  
                    "   ▄███▄▄▄▄███▄▄  \n",  
                    "  ▀▀███▀▀▀▀███▀   \n",
                    "    ███    ███    \n",
                    "    ███    ███    \n",  
                    "    ███    █▀     "     
                };
            }

            else if (symbol == 'e')
            {
                letter = {
                    "     ▄████████  \n",
                    "    ███    ███  \n", 
                    "    ███    █▀   \n",  
                    "   ▄███▄▄▄      \n",  
                    "  ▀▀███▀▀▀      \n",
                    "    ███    █▄   \n",
                    "    ███    ███  \n",    
                    "    ██████████  "  
                };
            }

            else if (symbol == 'r')
            {
                letter = {
                    "     ▄████████  \n",
                    "    ███    ███  \n",  
                    "    ███    ███  \n",  
                    "   ▄███▄▄▄▄██   \n",  
                    "  ▀▀███▀▀▀▀▀    \n", 
                    "  ▀███████████  \n",
                    "    ███    ███  \n",    
                    "    ███    ███  "  
                };
            }

            else if (symbol == 'o')
            {
                letter = {
                    "   ▄██████▄   \n",
                    "  ███    ███  \n",  
                    "  ███    ███  \n",  
                    "  ███    ███  \n", 
                    "  ███    ███  \n",  
                    "  ███    ███  \n",
                    "  ███    ███  \n",   
                    "   ▀██████▀   "  
                };
            }

            else if (symbol == 's')
            {
                letter = {
                    "     ▄████████  \n",
                    "    ███    ███  \n",  
                    "    ███    █▀   \n",  
                    "    ███         \n",  
                    "  ▀███████████  \n",  
                    "           ███  \n",
                    "      ▄█   ███  \n",    
                    "    ▄████████▀  "  
                };
            }

            else if (symbol == 'a')
            {
                letter = {
                    "     ▄████████   \n",
                    "    ███    ███   \n",  
                    "    ███    ███   \n",  
                    "    ███    ███   \n",  
                    "   ▀███████████  \n", 
                    "    ███    ███   \n",
                    "    ███    ███   \n",    
                    "    ███    █▀    "  
                };
            }

            else if (symbol == 'n')
            {
                letter = {
                    "  ███▄▄▄▄     \n",
                    "  ███▀▀▀██▄   \n",  
                    "  ███    ███  \n",  
                    "  ███    ███  \n",  
                    "  ███    ███  \n",  
                    "  ███    ███  \n",
                    "  ███    ███  \n",    
                    "   ▀█    █▀   "  
                };
            }

            else if (symbol == 'd')
            {
                letter = {
                    "  ████████▄   \n",
                    "  ███   ▀███  \n",
                    "  ███    ███  \n",  
                    "  ███    ███  \n",  
                    "  ███    ███  \n",  
                    "  ███    ███  \n",
                    "  ███    ███  \n",    
                    "  ████████▀   "  
                };
            }

            else if (symbol == 'm')
            {
                letter = {
                    "    ▄▄▄▄███▄▄▄▄    \n",
                    "  ▄██▀▀▀███▀▀▀██▄  \n",  
                    "  ███   ███   ███  \n",  
                    "  ███   ███   ███  \n",  
                    "  ███   ███   ███  \n",  
                    "  ███   ███   ███  \n",
                    "  ███   ███   ███  \n",    
                    "   ▀█   ███   █▀   "  
                };
            }

            else if (symbol == 'g')
            {
                letter = {
                    "    ▄██████▄    \n",
                    "    ███   ███   \n",  
                    "    ███   █▀    \n",  
                    "   ▄███         \n",  
                    "  ▀▀███ ████▄   \n",  
                    "    ███    ███  \n",
                    "    ███    ███  \n",    
                    "    ████████▀   "  
                };
            }

            else if (symbol == 'i')
            {
                letter = {
                    "   ▄█   \n",
                    "  ███   \n",  
                    "  ███▌  \n",  
                    "  ███▌  \n",  
                    "  ███▌  \n",  
                    "  ███   \n",
                    "  ███   \n",    
                    "  █▀    "  
                };
            }

            else if (symbol == 'c')
            {
                letter = {
                    "   ▄████████  \n",
                    "  ███    ███  \n",
                    "  ███    █▀   \n",  
                    "  ███         \n",  
                    "  ███         \n", 
                    "  ███    █▄   \n",
                    "  ███    ███  \n",   
                    "  ████████▀   "  
                };
            }

            for (int i = 0; i < letter.size(); i++)
            {
                COORD coordLocal = GetConsoleCursorPosition(console);
                coordLocal.X = coordX;
                SetConsoleCursorPosition(console, coordLocal);

                std::cout << letter[i];
            }
        }                                                                                                          

        void drawMenu()
        {
            std::cout << "\n\n\n";

            for (int i = 0; i < menu.size(); i++)
            {
                if (mainmenu::logic::currentPoint == i)
                {
                    SetConsoleTextAttribute(console, 9);
                }

                std::cout << "\t\t\t     " << menu[i] << "\n\n";
                SetConsoleTextAttribute(console, 15);
            }
        }
    }
}

#endif