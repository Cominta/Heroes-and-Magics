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
        inline std::map<heroes::heroesClass, heroes::Attributes>* returnCurrentTeam();
        inline std::map<heroes::heroesClass, heroes::Attributes>* returnEnemyTeam();
        Directions checkDirections();
        void moveCursor(int keyCode);
        void endTurn();
        void moveUnit();
        void loopGenerate();
        void animAttackLong();
        bool checkNextUnit();
        template <typename T>
        int linearSearch(T element, std::vector<T> array);

        enum class States // я не знаю почему я сделал переключалку нормальную только в главном меню и тут, а других местах дерьмово..
        {
            MENU,
            MOVE_CHOICE,
            ATTACK_CHOICE_DIFFERENT,
            ATTACK_CHOICE_SIDE,
            ATTACK_LONG,
            SHOW_HP
        };

        enum sides
        {
            LEFT,
            RIGHT,
            UP,
            DOWN
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
        int currentPointSide = 0;
        int currentPointAttack = 0;
        int animX;
        int animY;
        sides side;
        std::string symbol = "©";
        bool changeFirst = false;
        bool longAttack;
        bool variantOfAttack; // true - long, false - near

        // карта
        std::vector<std::vector<std::string>> map;
        int width;
        int height;

        int update(int keyCode)
        {
            // returnCurrentTeam()[heroes::heroesClass::ANGEL].health = 30;
            if (keyCode == KeyCode::ESCAPE)
            {
                sounds::play("enter", sounds::volumeEnter);

                endTurn();
                currentTeam = false;
                currentState = States::MENU;
                return -1;
            }   

            if (currentState == States::MENU)
            {
                checkPoint(currentPointMenu, keyCode, 2);
            }

            else if (currentState == States::MOVE_CHOICE) // двигаем курсор
            {
                sounds::play("move_cursor", sounds::volumeMoveCursor);
                moveCursor(keyCode);
            }

            else if (currentState == States::ATTACK_CHOICE_DIFFERENT)
            {
                if (longAttack)
                {
                    checkPoint(currentPointAttack, keyCode, 1);
                }

                else 
                {
                    checkPoint(currentPointAttack, keyCode, 0);
                }
            }

            else if (currentState == States::ATTACK_CHOICE_SIDE)
            {
                checkPoint(currentPointSide, keyCode, 3);
            }

            else if (currentState == States::ATTACK_LONG)
            {
                animAttackLong();
                Sleep(200);
                return 1;
            }

            // проверяем клавиши
            if (currentState == States::MENU && keyCode == KeyCode::ENTER) // выбрали пункт в меню
            {
                sounds::play("enter", sounds::volumeEnter);

                startX = (*returnCurrentTeam())[currentUnit].x;
                startY = (*returnCurrentTeam())[currentUnit].y;

                switch (currentPointMenu)
                {
                    case 0:
                        currentState = States::MOVE_CHOICE;
                        moveX = startX;
                        moveY = startY;

                        SetConsoleCursorInfo(console, &visible);

                        break;

                    case 1:
                        animX = startX;
                        animY = startY;
                        currentState = States::ATTACK_CHOICE_DIFFERENT;

                        if ((*returnCurrentTeam())[currentUnit].attackLongMax > 0)
                        {
                            longAttack = true;
                        }

                        else 
                        {
                            longAttack = false;
                        }

                        break;

                    case 2:
                        currentState = States::SHOW_HP;
                        break;
                }
            }

            else if (currentState == States::MOVE_CHOICE && keyCode == KeyCode::ENTER && map[moveY][moveX] != heroes::findSymbol(currentUnit)) // выбрали куда пойти
            {
                sounds::play("move_unit", sounds::volumeMoveUnit);
                moveUnit();
                endTurn();
            }

            else if (currentState == States::ATTACK_CHOICE_DIFFERENT && keyCode == KeyCode::ENTER)
            {
                currentState = States::ATTACK_CHOICE_SIDE;
                
                if (currentPointAttack == 1)
                {
                    variantOfAttack = true;
                }

                else 
                {
                    variantOfAttack = false;
                }
            }

            else if (currentState == States::ATTACK_CHOICE_SIDE && keyCode == KeyCode::ENTER)
            {
                currentState = States::ATTACK_LONG;
                side = (sides)currentPointSide;

                return 1;
            }

            else if (currentState != States::MENU && currentState != States::ATTACK_LONG && keyCode == KeyCode::SPACE) // вышли 
            {
                sounds::play("enter", sounds::volumeEnter);

                if (currentState == States::ATTACK_CHOICE_SIDE)
                {
                    currentState = States::ATTACK_CHOICE_DIFFERENT;
                }

                else
                {
                    currentState = States::MENU;
                }

                SetConsoleCursorInfo(console, &invisible);
            }

            return 0;
        }       

        inline std::map<heroes::heroesClass, heroes::Attributes>* returnCurrentTeam()
        {
            return (currentTeam ? &secondTeam : &firstTeam);
        }

        inline std::map<heroes::heroesClass, heroes::Attributes>* returnEnemyTeam()
        {
            return (currentTeam ? &firstTeam : &secondTeam);
        }

        void generateUnit()
        {
            std::map<heroes::heroesClass, heroes::Attributes>* team = returnCurrentTeam();
            int unit = rand() % (team->size() - 0) - 1;
            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = team->begin();

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
            int unitsRange = (*returnCurrentTeam())[currentUnit].speed;
            int xUnit = (*returnCurrentTeam())[currentUnit].x;
            int yUnit = (*returnCurrentTeam())[currentUnit].y;
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
            heroes::Attributes attrNew = (*returnCurrentTeam())[currentUnit];
            int oldX = attrNew.x;
            int oldY = attrNew.y;
            attrNew.x = moveX;
            attrNew.y = moveY;

            map[attrNew.y][attrNew.x] = heroes::findSymbol(currentUnit);
            (*returnCurrentTeam())[currentUnit] = attrNew;
            
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

            changeFirst = false;

            loopGenerate();
        }

        void animAttackLong()
        {
            if (!changeFirst)
            {
                changeFirst = true;
            }

            else 
            {
                map[animY][animX] = " ";
            }

            if (side == sides::RIGHT)
            {
                animX++;
            }

            else if (side == sides::LEFT)
            {
                animX--;
            }

            else if (side == sides::UP)
            {
                animY--;
            }

            else if (side == sides::DOWN)
            {
                animY++;
            }

            if (checkNextUnit())
            {
                return;
            }

            map[animY][animX] = symbol;
        }

        bool checkNextUnit()
        {
            if (linearSearch(map[animY][animX], map::logic::elements) != -1 || map[animY][animX] == " ")
            {
                return false;
            }

            std::map<heroes::heroesClass, heroes::Attributes>* enemyTeam = returnEnemyTeam();
            std::map<heroes::heroesClass, heroes::Attributes>* currentTeam = returnCurrentTeam();
            heroes::Attributes* unitEnemy = &(*enemyTeam)[heroes::symbols[map[animY][animX]]];
            heroes::Attributes* unitCurrent = &(*currentTeam)[currentUnit];

            if (enemyTeam->count(heroes::symbols[map[animY][animX]]) == 1)
            {
                unitEnemy->health -= unitCurrent->attackLongMax;
            }

            endTurn();

            return true;
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