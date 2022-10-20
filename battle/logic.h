#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include "../help.h"
#include <iostream>
#include <time.h>

namespace battle
{
    namespace logic
    {
        struct Move;
        void generateUnit();
        inline std::map<heroes::heroesClass, heroes::Attributes>& returnCurrentTeam();
        void checkMove();
        void moveCursor(int keyCode);
        void endTurn();
        void moveUnit();
        void loopGenerate();

        struct Move
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
        Move currentMoves;

        CONSOLE_CURSOR_INFO visible;
        CONSOLE_CURSOR_INFO invisible;

        bool move = false; // что-то типо состояния. в думал, может сделать нормальный переключатель состояний, но и так сойдет
        int startX;
        int startY;
        int moveX;
        int moveY;

        std::vector<std::vector<std::string>> map;
        int width;
        int height;

        int update(int keyCode)
        {
            if (keyCode == KeyCode::ESCAPE)
            {
                endTurn();
                currentTeam = false;
                return -1;
            }   

            if (!move)
            {
                checkPoint(currentPointMenu, keyCode, 1);
            }

            else // двигаем курсор
            {
                moveCursor(keyCode);
            }

            // проверяем клавиши
            if (!move && keyCode == KeyCode::ENTER) // выбрали пункт в меню
            {
                switch (currentPointMenu)
                {
                    case 0:
                        move = true;
                        startX = returnCurrentTeam()[currentUnit].x;
                        startY = returnCurrentTeam()[currentUnit].y;
                        moveX = startX;
                        moveY = startY;

                        SetConsoleCursorInfo(console, &visible);

                        break;
                }
            }

            else if (move && keyCode == KeyCode::ENTER && map[moveY][moveX] != heroes::findSymbol(currentUnit)) // выбрали куда пойти
            {
                moveUnit();
                endTurn();
            }

            else if (move && keyCode == KeyCode::SPACE) // вышли из выбора точки передвижения, передумали 
            {
                move = false;
                SetConsoleCursorInfo(console, &invisible);
            }
        }       

        inline std::map<heroes::heroesClass, heroes::Attributes>& returnCurrentTeam()
        {
            return (currentTeam ? secondTeam : firstTeam);
        }

        void generateUnit()
        {
            std::map<heroes::heroesClass, heroes::Attributes> team = returnCurrentTeam();
            int unit = rand() % (team.size() - 0) - 0;
            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = team.begin();

            for (int i = 0; i <= unit; i++)
            {
                it++;
            }

            currentUnit = it->first;
            checkMove();
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

        void checkMove()
        {
            int unitsSpeed = returnCurrentTeam()[currentUnit].speed;
            int xUnit = returnCurrentTeam()[currentUnit].x;
            int yUnit = returnCurrentTeam()[currentUnit].y;
            Move result;

            bool left = true;
            bool right = true;

            for (int i = 1; i <= unitsSpeed; i++) // x
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

            for (int i = 1; i <= unitsSpeed; i++) // y
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

            currentMoves = result;
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

            move = false;
            moveX = 0;
            moveY = 0;

            currentTeam = !currentTeam;
            currentMoves = {};

            loopGenerate();
        }
    }
}

#endif 