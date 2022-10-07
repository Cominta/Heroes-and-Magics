#include <conio.h>

#include "mainmenu/graphics.h"
#include "mainmenu/logic.h"

#include "battle/graphics.h"
#include "battle/logic.h"

#include "army/graphics.h"
#include "army/logic.h"

void mainLoop();

enum class States
{
    MAIN_MENU,
    BATTLE,
    ARMY
};

States currentState = States::MAIN_MENU;

int main()
{
    mainLoop();
    return 0;
}

void mainLoop()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;

	cursor.bVisible = false;
	cursor.dwSize = 1;

    SetConsoleCursorInfo(console, &cursor);

    std::map<heroes::heroesClass, heroes::Attributes> firstTeam = {
        {heroes::heroesClass::FANATIC, heroes::attributes[heroes::heroesClass::FANATIC]},
        {heroes::heroesClass::SHOOTER, heroes::attributes[heroes::heroesClass::SHOOTER]},
        {heroes::heroesClass::SWORDSMAN, heroes::attributes[heroes::heroesClass::SWORDSMAN]},
        {heroes::heroesClass::CRUSADER, heroes::attributes[heroes::heroesClass::CRUSADER]},
        {heroes::heroesClass::RIDER, heroes::attributes[heroes::heroesClass::RIDER]},
        {heroes::heroesClass::ARCHANGEL, heroes::attributes[heroes::heroesClass::ARCHANGEL]},
        {heroes::heroesClass::ARCHIGRIFON, heroes::attributes[heroes::heroesClass::ARCHIGRIFON]},
        {heroes::heroesClass::MONK, heroes::attributes[heroes::heroesClass::MONK]},
        {heroes::heroesClass::SPEARMAN, heroes::attributes[heroes::heroesClass::SPEARMAN]},
        {heroes::heroesClass::ANGEL, heroes::attributes[heroes::heroesClass::ANGEL]}
    };
    std::map<heroes::heroesClass, heroes::Attributes> secondTeam = {
        {heroes::heroesClass::FANATIC, heroes::attributes[heroes::heroesClass::FANATIC]},
        {heroes::heroesClass::SHOOTER, heroes::attributes[heroes::heroesClass::SHOOTER]},
        {heroes::heroesClass::SWORDSMAN, heroes::attributes[heroes::heroesClass::SWORDSMAN]},
        {heroes::heroesClass::CRUSADER, heroes::attributes[heroes::heroesClass::CRUSADER]},
        {heroes::heroesClass::RIDER, heroes::attributes[heroes::heroesClass::RIDER]},
        {heroes::heroesClass::ARCHANGEL, heroes::attributes[heroes::heroesClass::ARCHANGEL]},
        {heroes::heroesClass::ARCHIGRIFON, heroes::attributes[heroes::heroesClass::ARCHIGRIFON]},
        {heroes::heroesClass::MONK, heroes::attributes[heroes::heroesClass::MONK]},
        {heroes::heroesClass::SPEARMAN, heroes::attributes[heroes::heroesClass::SPEARMAN]},
        {heroes::heroesClass::ANGEL, heroes::attributes[heroes::heroesClass::ANGEL]}
    };

    CONSOLE_FONT_INFOEX fontInfo;
    GetCurrentConsoleFontEx(console, TRUE, &fontInfo); // Получить текущий шрифт

    fontInfo.dwFontSize.X = 2; // Размер (в логических единицах)

    SetCurrentConsoleFontEx(console, TRUE, &fontInfo); // Установить новый

    while (true)
    {

        if (currentState == States::MAIN_MENU)
        {
            system("cls");
            mainmenu::graphics::display();

            int code = _getch();

            if (code == 224) 
            { 
				code = _getch();
			}

            int result = mainmenu::logic::update(code, mainmenu::graphics::menu.size()); // -1 - ничего, 0 - игра, 1 - армия, 2 - выход

            switch (result)
            {
                case 0:
                    currentState = States::BATTLE;
                    break;

                case 1:
                    CONSOLE_CURSOR_INFO cursor;

                    cursor.bVisible = true;
                    cursor.dwSize = 1;

                    SetConsoleCursorInfo(console, &cursor);
                    currentState = States::ARMY;
                    break;

                case 2:
                    _exit(3);
                    break;
            }
        }

        else if (currentState == States::BATTLE)
        {

        }

        else if (currentState == States::ARMY)
        {
            Sleep(2000);
            system("cls");
            army::graphics::display(firstTeam, secondTeam);
            army::logic::update();
        }
    }
}