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
        void update()
        {
            
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