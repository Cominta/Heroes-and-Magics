#ifndef ARMY_LOGIC_H
#define ARMY_LOGIC_H

#include "../help.h"

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

                map[y][x] = heroes::findSymbol(choiceChange[currentPointEdit]);
            }

            return 0;
        }

        int checkKeys(int code)
        {
            if (editUnit)
            {
                checkPoint(currentPointEdit, code, 9);
            }

            else
            {
                checkPoint(currentPoint, code, 9);
            }

            if ((code == KeyCode::LEFT || code == KeyCode::RIGHT) && !editUnit)
            {
                currentTeam = !currentTeam;
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

            for (int i = 0; i < heroes::count - 1; i++)
            {
                if (i == currentPoint)
                {
                    heroes::Attributes attr =  heroes::attributes[choiceChange[currentPointEdit]];
                    attr.x = team[teamKeys[currentPoint]].x;
                    attr.y = team[teamKeys[currentPoint]].y;
                    newTeam.insert({choiceChange[currentPointEdit], attr});

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
            currentPointEdit = 0;

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