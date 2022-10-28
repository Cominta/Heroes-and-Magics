#include <conio.h>

#include "mainmenu/graphics.h"
#include "mainmenu/logic.h"

#include "battle/graphics.h"
#include "battle/logic.h"

#include "army/graphics.h"
#include "army/logic.h"

#include "map/logic.h"
#include "map/graphics.h"

void mainLoop();
int getCode();
void changeFont(int sizeY);

enum class States
{
    MAIN_MENU,
    BATTLE,
    ARMY,
    MAP
};

States currentState = States::MAIN_MENU;

int main()
{
    mainLoop();

    return 0;
}

void mainLoop()
{
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

    int width = 30;
    int height = 20;
    std::vector<std::vector<std::string>> map;

    map::logic::initMap(map, firstTeam, secondTeam, width, height);

    bool change = false;

    while (true)
    {
        if (currentState == States::MAIN_MENU)
        {
            if (!change)
            {
                changeFont(10);
                system("MODE 100, 70");
                change = true;
            }

            system("cls");
            mainmenu::graphics::display();

            int code = getCode();
            int result = mainmenu::logic::update(code, mainmenu::graphics::menu.size()); // -1 - ничего, 0 - игра, 1 - армия, 2 - карта, 3 - выход

            if (result != -1)
            {
                changeFont(20);
                system("MODE 100,30");
                change = false;
            }

            switch (result)
            {
                case 0:
                    currentState = States::BATTLE;
                    battle::logic::init(firstTeam, secondTeam, map, width, height);
                    break;

                case 1:
                    system("MODE 110,30");
                    currentState = States::ARMY;
                    break;

                case 2:
                    currentState = States::MAP;
                    break;

                case 3:
                    _exit(3);
                    break;
            }
        }

        else if (currentState == States::BATTLE)
        {
            system("cls");

            battle::graphics::display();

            int code = getCode();
            int result = battle::logic::update(code);

            if (result == -1)
            {
                currentState = States::MAIN_MENU;
            }
        }

        else if (currentState == States::ARMY)
        {
            system("cls");

            army::graphics::display(map, firstTeam, secondTeam, width, height);

            int code = getCode();
            int result = army::logic::update(code, firstTeam, secondTeam, map);

            if (result == -1)
            {
                currentState = States::MAIN_MENU;
            }
        }

        else if (currentState == States::MAP)
        {
            system("cls");
            map::graphics::display(map, width, height);

            int code = getCode();
            int result = map::logic::update(map, code, width, height);

            if (result == -1)
            {
                currentState = States::MAIN_MENU;
            }
        }
    }
}

int getCode()
{
    int code = _getch();

    if (code == 224)
    {
        code = _getch();
    }

    return code;
}

void changeFont(int sizeY)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof fontInfo;
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 0;
    fontInfo.dwFontSize.Y = sizeY;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    std::wcscpy(fontInfo.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(console, FALSE, &fontInfo);
}
