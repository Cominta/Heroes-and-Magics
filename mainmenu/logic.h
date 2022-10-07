#ifndef MAIN_MENU_LOGIC_H
#define MAIN_MENU_LOGIC_H

#include "../help.h"

namespace mainmenu
{
    namespace logic
    {
        void updatePoint(int keyCode, int countPoints);

        int currentPoint = 0;

        int update(int keyCode, int countPoints)
        {
            mainmenu::logic::updatePoint(keyCode, countPoints);
            
            if (keyCode == KeyCode::ENTER)
            {
                return currentPoint;
            }

            return -1;
        }

        void updatePoint(int keyCode, int countPoints)
        {
            if (keyCode == KeyCode::DOWN)
            {
                currentPoint++;
            }

            else if (keyCode == KeyCode::UP)
            {
                currentPoint--;
            }

            if (currentPoint > countPoints - 1)
            {
                currentPoint = 0;
            }

            else if (currentPoint < 0)
            {
                currentPoint = countPoints - 1;
            }
        }
    }
}

#endif