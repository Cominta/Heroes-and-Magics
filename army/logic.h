#ifndef ARMY_LOGIC_H
#define ARMY_LOGIC_H

#include "../help.h"

namespace army
{
    namespace logic
    {
        int checkKeys(int code);
        std::vector<heroes::heroesClass> checkUnitsPrint(std::map<heroes::heroesClass, heroes::Attributes> team);
        void changeUnit(std::map<heroes::heroesClass, heroes::Attributes>& team);

        int currentPoint = 0;
        int currentPointEdit = 0;
        bool currentTeam = false; // false - первая команда, true - вторая

        std::vector<heroes::heroesClass> choiceChange;
        bool editUnit = false;

        int update(int code, std::map<heroes::heroesClass, heroes::Attributes>& firstTeam, std::map<heroes::heroesClass, heroes::Attributes>& secondTeam)
        {
            if (code == KeyCode::ESCAPE)
            {
                return -1;
            }

            if (checkKeys(code) == 2)
            {
                if (currentTeam)
                {
                    changeUnit(secondTeam);
                }

                else 
                {
                    changeUnit(firstTeam);
                }
            }

            return 0;
        }

        int checkKeys(int code)
        {
            if (code == KeyCode::UP)
            {
                if (editUnit)
                {
                    currentPointEdit--;

                    if (currentPointEdit < 0)
                    {
                        currentPointEdit = choiceChange.size() - 1;
                    }
                }

                else 
                {
                    currentPoint--;

                    if (currentPoint < 0)
                    {
                        currentPoint = 9;
                    }
                }
            }

            else if (code == KeyCode::DOWN)
            {
                if (editUnit)
                {
                    currentPointEdit++;

                    if (currentPointEdit > choiceChange.size() - 1)
                    {
                        currentPointEdit = 0;
                    }
                }

                else 
                {
                    currentPoint++;

                    if (currentPoint > 9)
                    {
                        currentPoint = 0;
                    }
                }
            }

            else if ((code == KeyCode::LEFT || code == KeyCode::RIGHT) && !editUnit)
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

        void changeUnit(std::map<heroes::heroesClass, heroes::Attributes>& team)
        {
            std::vector<heroes::heroesClass> teamKeys;

            for (auto& heroe : team)
            {
                teamKeys.push_back(heroe.first);
            }

            std::map<heroes::heroesClass, heroes::Attributes>::iterator it = team.find(teamKeys[currentPoint]);
            
            team.insert(it, std::pair<heroes::heroesClass, heroes::Attributes> {choiceChange[currentPointEdit], heroes::attributes[choiceChange[currentPointEdit]]});
            it--;
            team.erase(it);

            editUnit = false;
            currentPointEdit = 0;
        }
    }
}

#endif