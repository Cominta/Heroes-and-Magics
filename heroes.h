#ifndef HEROES_H
#define HEROES_H

#include <string>
#include <map>
#include <vector>

namespace heroes
{
    // тут прописано что-то типо шаблона героев
    const int count = 11;

    enum heroesClass
    {
        ANGEL,
        ARCHANGEL,
        ARCHIGRIFON,
        CENTAUR,
        CRUSADER,
        FANATIC,
        MONK,
        RIDER,
        SHOOTER,
        SWORDSMAN,
        SPEARMAN,
    };
  
    struct Attributes
    {
        int attackNearMin;
        int attackNearMax;
        int attackLongMin;
        int attackLongMax;
        int armor;
        int health;
        int speed;
        int x;
        int y;
    };

    std::map<heroesClass, Attributes> attributes = {
        {heroesClass::FANATIC, Attributes {10, 12, 24, 26, 10, 30, 2}},
        {heroesClass::SHOOTER, Attributes {2, 3, 24, 26, 3, 10, 2}},
        {heroesClass::SWORDSMAN, Attributes {6, 9, 0, 0, 12, 35, 3}},
        {heroesClass::CRUSADER, Attributes {7, 10, 0, 0, 12, 35, 3}},
        {heroesClass::RIDER, Attributes {15, 25, 0, 0, 15, 100, 5}},
        {heroesClass::ARCHANGEL, Attributes {50, 55, 0, 0, 50, 250, 9}},
        {heroesClass::ARCHIGRIFON, Attributes {3, 6, 0, 0, 9, 25, 7}},
        {heroesClass::MONK, Attributes {10, 12, 12, 14, 7, 30, 2}},
        {heroesClass::SPEARMAN, Attributes {1, 3, 0, 0, 5, 10, 3}},
        {heroesClass::ANGEL, Attributes {50, 52, 0, 0, 20, 200, 7}},
        {heroesClass::CENTAUR, Attributes {5, 7, 0, 0, 3, 8, 3}}
    };

    std::map<std::string, heroesClass> symbols = {
        {"ⱹ", heroesClass::FANATIC},
        {">", heroesClass::SHOOTER},
        {"‡", heroesClass::SWORDSMAN},
        {"✟", heroesClass::CRUSADER},
        {"ﬓ", heroesClass::RIDER},
        {"╬", heroesClass::ARCHANGEL},
        {"╪", heroesClass::ARCHIGRIFON},
        {"ʎ", heroesClass::MONK},
        {"/", heroesClass::SPEARMAN},
        {"ô", heroesClass::ANGEL},
        {"∩", heroesClass::CENTAUR}
    };

    std::map<heroesClass, std::string> names = {
        {heroesClass::FANATIC,"Fanatic"},
        {heroesClass::SHOOTER, "Shooter"},
        {heroesClass::SWORDSMAN, "Swordsman"},
        {heroesClass::CRUSADER, "Crusader"},
        {heroesClass::RIDER, "Rider"},
        {heroesClass::ARCHANGEL, "Archangel"},
        {heroesClass::ARCHIGRIFON, "Archigrifon"},
        {heroesClass::MONK, "Monk"},
        {heroesClass::SPEARMAN, "Spearman"},
        {heroesClass::ANGEL, "Angel"},
        {heroesClass::CENTAUR, "Centaur"}
    };

    std::string findSymbol(heroes::heroesClass find)
    {
        for (auto& heroe : heroes::symbols)
        {
            if (heroe.second == find)
            {
                return heroe.first;
            }

        }

        return "!";
    }
}

#endif 