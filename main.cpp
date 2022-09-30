#include <conio.h>
#include <Windows.h>

#include "mainmenu/graphics.h"
#include "mainmenu/logic.h"

#include "battle/graphics.h"
#include "battle/logic.h"

enum class States
{
    MAIN_MENU,
    BATTLE
};

States currentState = States::MAIN_MENU;

int main()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;

	cursor.bVisible = false;
	cursor.dwSize = 1;

    SetConsoleCursorInfo(console, &cursor);

    // SetConsoleCP(GetACP());
    // SetConsoleOutputCP(GetACP());

    // mainmenu::graphics::drawNameFistTime();

    while (true)
    {
        if (currentState == States::MAIN_MENU)
        {
            mainmenu::graphics::display();

            int code = _getch();

            if (code == 224) 
            { 
				code = _getch();
			}

            int result = mainmenu::logic::update(code, mainmenu::graphics::menu.size()); // -1 - ничего, 0 - игра, 1 - магазин, 2 - армия, 3 - выход

            switch (result)
            {
                case 0:
                    currentState = States::BATTLE;
                    break;

                case 3:
                    _exit(3);
                    break;
            }
        }

        else if (currentState == States::BATTLE)
        {

        }
    }

    return 0;
}