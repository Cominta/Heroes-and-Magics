#ifndef ARMY_LOGIC_H
#define ARMY_LOGIC_H

#include "../help.h"
#include <math.h>

namespace army
{
    namespace logic
    {
        int checkKeys(int code);
        std::vector<heroes::heroesClass> checkUnitsPrint(std::map<heroes::heroesClass, heroes::Attributes> team);
        std::map<heroes::heroesClass, heroes::Attributes> changeUnit(std::map<heroes::heroesClass, heroes::Attributes> team, int& x, int& y);
        void checkColor(std::map<heroes::heroesClass, heroes::Attributes> firstTeam, std::map<heroes::heroesClass, heroes::Attributes> secondTeam); // определяем какого юнита красить

        int currentPoint = 0;
        int currentPointEdit = 0;
        int currentPage = 0;
        int maxPage;
        bool currentTeam = false; // false - первая команда, true - вторая
        int xToColor = -1;
        int yToColor = -1;

        std::vector<heroes::heroesClass> choiceChange;
        bool editUnit = false;

        int update(int code, std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam, std::vector<std::vector<std::string>>& map)
        {
            if (code == KeyCode::ESCAPE)
            {
                return -1;
            }

            if (checkKeys(code) == 2)
            {
                int x, y;

                if (currentTeam)
                {
                    secondTeam = changeUnit(secondTeam, x, y);
                }

                else 
                {
                    firstTeam = changeUnit(firstTeam, x, y);
                }

                map[y][x] = heroes::findSymbol(choiceChange[currentPointEdit + currentPage * 10]);
                currentPointEdit = 0;
                currentPage = 0;
            }

            return 0;
        }

        int checkKeys(int code)
        {
            if (editUnit && currentPage != maxPage)
            {
                checkPoint(currentPointEdit, code, 9);
            }

            else if (editUnit && currentPage == maxPage)
            {
                checkPoint(currentPointEdit, code, choiceChange.size() % 10 - 1);
            }

            else
            {
                checkPoint(currentPoint, code, 9);
            }

            if ((code == KeyCode::LEFT || code == KeyCode::RIGHT) && !editUnit)
            {
                currentTeam = !currentTeam;
            }

            else if (code == KeyCode::LEFT)
            {
                currentPage--;

                if (currentPage < 0)
                {
                    currentPage = maxPage;
                }
            }

            else if (code == KeyCode::RIGHT)
            {
                currentPage++;

                if (currentPage > maxPage)
                {
                    currentPage = 0;
                }
            }

            if (currentPage == maxPage && currentPointEdit > choiceChange.size() % 10 - 1)
            {
                currentPointEdit = choiceChange.size() % 10 - 1;
            }

            else if (code == KeyCode::ENTER)
            {
                if (editUnit)
                {
                    return 2;
                }

                else 
                {
                    editUnit = true;
                }
            }

            return 0;
        }

        std::vector<heroes::heroesClass> checkUnitsPrint(std::map<heroes::heroesClass, heroes::Attributes> team)
        {
            std::vector<heroes::heroesClass> keys;
            std::vector<heroes::heroesClass> toPrint;

            for (auto& heroe : team)
            {
                keys.push_back(heroe.first);
            }

            for (int i = 0; i < heroes::count; i++)
            {
                heroes::heroesClass currentUnit = (heroes::heroesClass)i;
                bool print = true;

                for (int k = 0; k < keys.size(); k++)
                {
                    if (keys[k] == currentUnit)
                    {   
                        print = false;
                        break;
                    }
                }

                if (print)
                {
                    toPrint.push_back((heroes::heroesClass)i);
                }
            }

            choiceChange = toPrint;
            maxPage = ceil(toPrint.size() / 10.0f) - 1;
            return toPrint;
        }

        std::map<heroes::heroesClass, heroes::Attributes> changeUnit(std::map<heroes::heroesClass, heroes::Attributes> team, int& x, int& y)
        {
            std::vector<heroes::heroesClass> teamKeys;

            for (auto& heroe : team)
            {
                teamKeys.push_back(heroe.first);
            }

            std::map<heroes::heroesClass, heroes::Attributes> newTeam;
            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = team.begin();

            for (int i = 0; i < 10; i++)
            {
                if (i == currentPoint)
                {
                    heroes::Attributes attr =  heroes::attributes[choiceChange[currentPointEdit + currentPage * 10]];
                    attr.x = team[teamKeys[currentPoint]].x;
                    attr.y = team[teamKeys[currentPoint]].y;
                    newTeam.insert({choiceChange[currentPointEdit + currentPage * 10], attr});

                    x = attr.x;
                    y = attr.y;
                }

                else 
                {
                    newTeam.insert({it->first, it->second});
                }

                it++;
            }

            editUnit = false;

            return newTeam;
        }

        void checkColor(std::map<heroes::heroesClass, heroes::Attributes> firstTeam, std::map<heroes::heroesClass, heroes::Attributes> secondTeam)
        {
            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = (currentTeam ? secondTeam.begin() : firstTeam.begin());

            for (int i = 0; i < currentPoint; i++)
            {
                it++;
            }

            xToColor = it->second.x;
            yToColor = it->second.y;
        }
    }
}

#endif