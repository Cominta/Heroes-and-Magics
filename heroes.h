#ifndef HEROES_H
#define HEROES_H

#include <string>
#include <map>
#include <vector>

namespace heroes
{
    // тут прописано что-то типо шаблона героев

    enum class heroesClass
    {
        FANATIC,
        SHOOTER,
        SWORDSMAN,
        CRUSADER,
        RIDER,
        ARCHANGEL,
        ARCHIGRIFON,
        MONK,
        SPEARMAN,
        ANGEL
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
        {heroesClass::ANGEL, Attributes {50, 52, 0, 0, 20, 200, 7}}
    };

    std::map<std::string, heroesClass> symbols = {
        {"ⱹ", heroesClass::FANATIC},
        {"▻", heroesClass::SHOOTER},
        {"‡", heroesClass::SWORDSMAN},
        {"✟", heroesClass::CRUSADER},
        {"ﬓ", heroesClass::RIDER},
        {"╬", heroesClass::ARCHANGEL},
        {"╪", heroesClass::ARCHIGRIFON},
        {"ʎ", heroesClass::MONK},
        {"/", heroesClass::SPEARMAN},
        {"ô", heroesClass::ANGEL}
    };
}

#endif 