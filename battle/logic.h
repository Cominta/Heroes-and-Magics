#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include "../help.h"
#include <iostream>
#include <time.h>
#include "../map/logic.h"

namespace battle
{
    namespace logic
    {
        struct Directions;
        void generateUnit();
        inline std::map<heroes::heroesClass, heroes::Attributes>& returnCurrentTeam();
        inline std::map<heroes::heroesClass, heroes::Attributes>& returnEnemyTeam();
        Directions checkDirections();
        void moveCursor(int keyCode);
        void endTurn();
        void moveUnit();
        void loopGenerate();
        Directions checkAttackNear();
        std::vector<std::pair<int, int>> checkAttackLong();
        template <typename T>
        int linearSearch(T element, std::vector<T> array);

        enum class States // я не знаю почему я сделал переключалку нормальную только в главном меню и тут, а других местах дерьмово..
        {
            MENU,
            MOVE_CHOICE,
            ATTACK_CHOICE,
            SHOW_HP
        };

        States currentState = States::MENU;

        struct Directions
        {
            int left = 0;
            int right = 0;
            int up = 0;
            int down = 0;
        };

        std::map<heroes::heroesClass, heroes::Attributes> firstTeam;
        std::map<heroes::heroesClass, heroes::Attributes> secondTeam;

        bool currentTeam = false;
        int currentPointMenu = 0;
        heroes::heroesClass currentUnit;
        Directions currentMoves;

        CONSOLE_CURSOR_INFO visible;
        CONSOLE_CURSOR_INFO invisible;

        int startX;
        int startY;

        // движение
        int moveX;
        int moveY;

        // атака
        std::vector<std::pair<int, int>> attack;

        std::vector<std::vector<std::string>> map;
        int width;
        int height;

        int update(int keyCode)
        {
            returnCurrentTeam()[heroes::heroesClass::ANGEL].health = 30;
            if (keyCode == KeyCode::ESCAPE)
            {
                endTurn();
                currentTeam = false;
                return -1;
            }   

            if (currentState == States::MENU)
            {
                checkPoint(currentPointMenu, keyCode, 2);
            }

            else if (currentState == States::MOVE_CHOICE)// двигаем курсор
            {
                moveCursor(keyCode);
            }

            // проверяем клавиши
            if (currentState == States::MENU && keyCode == KeyCode::ENTER) // выбрали пункт в меню
            {
                startX = returnCurrentTeam()[currentUnit].x;
                startY = returnCurrentTeam()[currentUnit].y;

                switch (currentPointMenu)
                {
                    case 0:
                        currentState = States::MOVE_CHOICE;
                        moveX = startX;
                        moveY = startY;

                        SetConsoleCursorInfo(console, &visible);

                        break;

                    case 1:
                        currentState = States::ATTACK_CHOICE;
                        // attack = checkAttackLong();
                        break;

                    case 2:
                        currentState = States::SHOW_HP;
                }
            }

            else if (currentState == States::MOVE_CHOICE && keyCode == KeyCode::ENTER && map[moveY][moveX] != heroes::findSymbol(currentUnit)) // выбрали куда пойти
            {
                moveUnit();
                endTurn();
            }

            else if (currentState != States::MENU && keyCode == KeyCode::SPACE) // вышли 
            {
                currentState = States::MENU;
                SetConsoleCursorInfo(console, &invisible);
            }
        }       

        inline std::map<heroes::heroesClass, heroes::Attributes>& returnCurrentTeam()
        {
            return (currentTeam ? secondTeam : firstTeam);
        }

        inline std::map<heroes::heroesClass, heroes::Attributes>& returnEnemyTeam()
        {
            return (currentTeam ? firstTeam : secondTeam);
        }

        void generateUnit()
        {
            std::map<heroes::heroesClass, heroes::Attributes> team = returnCurrentTeam();
            int unit = rand() % (team.size() - 0) - 1;
            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = team.begin();

            for (int i = 0; i <= unit; i++)
            {
                it++;
            }

            currentUnit = it->first;
            currentMoves = checkDirections();
        }

        void loopGenerate()
        {
            while (true)
            {
                generateUnit();

                if (currentMoves.left != 0 || currentMoves.right != 0 || currentMoves.up != 0 || currentMoves.down != 0)
                {
                    break;
                }
            }
        }

        void init(std::map<heroes::heroesClass, heroes::Attributes> firstTeamSave, std::map<heroes::heroesClass, heroes::Attributes> secondTeamSave, std::vector<std::vector<std::string>> mapSave, int widthSave, int heightSave)
        {
            srand(time(0));

            firstTeam = firstTeamSave;
            secondTeam = secondTeamSave;
            map = mapSave;
            width = widthSave;
            height = heightSave;

            visible.dwSize = 1;
            visible.bVisible = true;

            invisible.dwSize = 1;
            invisible.bVisible = false;

            SetConsoleCursorInfo(console, &invisible);

            loopGenerate();
        }

        Directions checkDirections()
        {
            int unitsRange = returnCurrentTeam()[currentUnit].speed;
            int xUnit = returnCurrentTeam()[currentUnit].x;
            int yUnit = returnCurrentTeam()[currentUnit].y;
            Directions result;

            bool left = true;
            bool right = true;

            for (int i = 1; i <= unitsRange; i++) // x
            {
                if (left && map[yUnit][xUnit - i] == " ")
                {
                    result.left++;
                }

                else 
                {
                    left = false;
                }

                if (right && map[yUnit][xUnit + i] == " ")
                {
                    result.right++;
                }

                else 
                {
                    right = false;
                }    
            }

            bool up = true;
            bool down = true;

            for (int i = 1; i <= unitsRange; i++) // y
            {
                if (up && map[yUnit - i][xUnit] == " ")
                {
                    result.up++;
                }

                else 
                {
                    up = false;
                }

                if (down && map[yUnit + i][xUnit] == " ")
                {
                    result.down++;
                }

                else 
                {
                    down = false;
                }
            }

            return result;
        }

        void mapToCoordCursor(int& x, int& y)
        {
            x += 8;
            y += 4;
        }

        void mapToCoordMap(int& x, int& y)
        {
            x -= 8;
            y -= 4;
        }

        void moveCursor(int keyCode)
        {
            if (moveY == startY && keyCode == KeyCode::LEFT && (moveX <= startX ? abs(moveX - startX) < currentMoves.left : true))
            {
                moveX--;
            }

            else if (moveY == startY && keyCode == KeyCode::RIGHT && (moveX >= startX ? abs(startX - moveX) < currentMoves.right : true))
            {
                moveX++;
            }

            else if (moveX == startX && keyCode == KeyCode::UP && (moveY <= startY ? abs(startY - moveY) < currentMoves.up : true))
            {
                moveY--;
            }

            else if (moveX == startX && keyCode == KeyCode::DOWN && (moveY >= startY ? abs(startY - moveY) < currentMoves.down : true))
            {
                moveY++;
            }
        }

        void moveUnit()
        {
            heroes::Attributes attrNew = returnCurrentTeam()[currentUnit];
            int oldX = attrNew.x;
            int oldY = attrNew.y;
            attrNew.x = moveX;
            attrNew.y = moveY;

            map[attrNew.y][attrNew.x] = heroes::findSymbol(currentUnit);
            returnCurrentTeam()[currentUnit] = attrNew;
            
            map[oldY][oldX] = " ";
        }

        void endTurn()
        {
            SetConsoleCursorInfo(console, &invisible);

            currentState = States::MENU;
            moveX = 0;
            moveY = 0;

            currentTeam = !currentTeam;
            currentMoves = {};

            loopGenerate();
        }

        Directions checkAttackNear()
        {
            Directions result;
            std::map<heroes::heroesClass, heroes::Attributes> enemyTeam = returnEnemyTeam();

            for (auto unit : enemyTeam)
            {
                std::cout << heroes::names[unit.first];
                Sleep(1000);
                if (unit.second.x == startX - 1 && unit.second.y == startY)
                {
                    result.left = 1;
                }

                else if (unit.second.x == startX + 1 && unit.second.y == startY)
                {
                    result.right = 1;
                }

                else if (unit.second.x == startX && unit.second.y == startY - 1)
                {
                    result.up = 1;
                }

                else if (unit.second.x == startX && unit.second.y == startY + 1)
                {
                    result.down = 1;
                }
            }

            return result;
        }

        std::vector<std::pair<int, int>> checkAttackLong()
        {
            int x = startX;
            int y = startY;
            std::vector<std::pair<int, int>> result;
            std::map<heroes::heroesClass, heroes::Attributes> enemyTeam = returnEnemyTeam();

            while (map[y][x] != map::logic::elements[0])
            {
                x--;

                if (enemyTeam.count(heroes::symbols[map[y][x]]) != 0 &&
                    enemyTeam[heroes::symbols[map[y][x]]].x == x && enemyTeam[heroes::symbols[map[y][x]]].y == y)
                {
                    result.push_back(std::pair<int, int> {x, y});
                }

                else if (map[y][x] != " ")
                {
                    break;
                }
            }

            x = startX;

            while (map[y][x] != map::logic::elements[0])
            {
                x++;

                if (enemyTeam.count(heroes::symbols[map[y][x]]) != 0 &&
                    enemyTeam[heroes::symbols[map[y][x]]].x == x && enemyTeam[heroes::symbols[map[y][x]]].y == y)
                {
                    result.push_back(std::pair<int, int> {x, y});
                    break;
                }

                else if (map[y][x] != " ")
                {
                    break;
                }
            }

            std::cout << enemyTeam[heroes::heroesClass::ANGEL].x << " " << enemyTeam[heroes::heroesClass::ANGEL].y;
            // std::cout << result.size();
            Sleep(1000);
        }

        template <typename T>
        int linearSearch(T element, std::vector<T> array)
        {
            for (int i = 0; i < array.size(); i++)
            {
                if (array[i] == element)
                {
                    return i;
                }
            }

            return -1;
        }
    }
}

#endif 