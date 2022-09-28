#include <conio.h>
#include <Windows.h>

#include "mainmenu/graphics.h"
#include "mainmenu/logic.h"

enum class States
{
    MAIN_MENU
};

States currentState = States::MAIN_MENU;

int main()
{
    mainmenu::graphics::display();

    while (true)
    {
        if (currentState == States::MAIN_MENU)
        {
            int code = _getch();

            if (code == 224) 
            { 
				code = _getch();
			}

            int result = mainmenu::logic::update(code, mainmenu::graphics::menu.size()); // -1 - ничего, 0 - игра, 1 - магазин, 2 - армия, 3 - выход

            switch (result)
            {
                case 3:
                    _exit(3);
                    break;
            }

            mainmenu::graphics::display();
        }
    }

    return 0;
}