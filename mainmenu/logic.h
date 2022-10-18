#ifndef MAIN_MENU_LOGIC_H
#define MAIN_MENU_LOGIC_H

#include "../help.h"

namespace mainmenu
{
    namespace logic
    {
        int currentPoint = 0;

        int update(int keyCode, int countPoints)
        {
            if (keyCode == KeyCode::ENTER)
            {
                return currentPoint;
            }

            checkPoint(currentPoint, keyCode, 3);

            return -1;
        }
    }
}

#endif