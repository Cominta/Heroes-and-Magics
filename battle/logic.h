#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

namespace battle
{
    namespace logic
    {
        std::map<heroes::heroesClass, heroes::Attributes> firstTeam;
        std::map<heroes::heroesClass, heroes::Attributes> secondTeam;

        void update()
        {

        }       

        void init(std::map<heroes::heroesClass, heroes::Attributes> firstTeamSave, std::map<heroes::heroesClass, heroes::Attributes> secondTeamSave)
        {
            firstTeam = firstTeamSave;
            secondTeam = secondTeamSave;
        }
    }
}

#endif 