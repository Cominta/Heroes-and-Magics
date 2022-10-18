#ifndef MAP_LOGIC_H
#define MAP_LOGIC_H

#include <vector>
#include <string>
#include <map>
#include "../heroes.h"

namespace map
{
    namespace logic
    {
        void moveCursor(int keyCode, int width, int height);
        void editMap(std::vector<std::vector<std::string>>& map);

        std::vector<std::string> elements = {
            "█", // стена
            "●", // камень
            "∆",  // дерево
            "░", // вода
            "☼" // мина
        };

        std::vector<std::string> legend = {
            "wall",
            "rock",
            "tree",
            "water",
            "bomb"
        };

        int currentPoint = 0;
        bool edit = false;
        int xEdit = 1;
        int yEdit = 1;

        CONSOLE_CURSOR_INFO cursor;

        int update(std::vector<std::vector<std::string>>& map, int keyCode, int width, int height)
        {
            if (keyCode == KeyCode::ESCAPE)
            {
                return -1;
            }

            else if (keyCode == KeyCode::ENTER)
            {
                if (edit == true)
                {
                    editMap(map);
                }

                else 
                {
                    cursor.dwSize = 1;
                    cursor.bVisible = true;
                    SetConsoleCursorInfo(console, &cursor);

                    edit = true;
                }
            }

            else if (keyCode == KeyCode::SPACE)
            {
                cursor.dwSize = 1;
                cursor.bVisible = false;
                SetConsoleCursorInfo(console, &cursor);

                edit = false;
            }

            if (!edit)
            {
                checkPoint(currentPoint, keyCode, elements.size() - 1);
            }

            else
            {
                moveCursor(keyCode, width, height);
            }
        }

        void editMap(std::vector<std::vector<std::string>>& map)
        {
            for (auto& heroeSymbol : heroes::symbols)
            {
                if (heroeSymbol.first == map[yEdit][xEdit])
                {
                    return;
                }
            }

            map[yEdit][xEdit] = elements[currentPoint];
        }

        void moveCursor(int keyCode, int width, int height)
        {
            if (keyCode == KeyCode::UP)
            {
                yEdit--;

                if (yEdit < 1)
                {
                    yEdit = height - 1;
                }
            }

            else if (keyCode == KeyCode::DOWN)
            {
                yEdit++;

                if (yEdit > height - 1)
                {
                    yEdit = 1;
                }
            }

            else if (keyCode == KeyCode::LEFT)
            {
                xEdit--;

                if (xEdit < 1)
                {
                    xEdit = width - 1;
                }
            }

            else if (keyCode == KeyCode::RIGHT)
            {
                xEdit++;

                if (xEdit > width - 1)
                {
                    xEdit = 1;
                }
            }
        }

        void initMap(std::vector<std::vector<std::string>>& map, std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam, int width, int height)
        {
            std::map<heroes::heroesClass, heroes::Attributes>::iterator firstIt = firstTeam.begin();
            std::map<heroes::heroesClass, heroes::Attributes>::iterator secondIt = secondTeam.begin();

            for (int y = 0; y <= height; y++)
            {
                map.push_back(std::vector<std::string> {});

                for (int x = 0; x <= width; x++)
                {
                    if (y == 0)
                    {
                        map[y].push_back("▄");
                    }

                    else if (y == height)
                    {
                        map[y].push_back("▀");
                    }

                    else if (x == 0 || x == width)
                    {
                        map[y].push_back("█");
                    }

                    else if (y >= 7 && y <= 11 && x <= 2)
                    {
                        firstIt->second.x = x;
                        firstIt->second.y = y;

                        map[y].push_back(heroes::findSymbol(firstIt->first));
                        firstIt++;
                    }

                    else if (y >= 7 && y <= 11 && x >= width - 2)
                    {
                        secondIt->second.x = x;
                        secondIt->second.y = y;

                        map[y].push_back(heroes::findSymbol(secondIt->first));
                        secondIt++;
                    }

                    else
                    {
                        map[y].push_back(" ");
                    }
                }
            }
        }
    }
}

#endif
