#ifndef MAIN_MENU_LOGIC_H
#define MAIN_MENU_LOGIC_H


enum KeyCode 
{ 
    ENTER = 13, 
    ESCAPE = 27, 
    SPACE = 32, 
    LEFT = 75, 
    RIGHT = 77, 
    UP = 72, 
    DOWN = 80 
};

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