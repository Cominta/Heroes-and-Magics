#ifndef HEROES_H
#define HEROES_H

#include <string>
#include <map>
#include <vector>

namespace heroes
{
    // тут прописано что-то типо шаблона героев
    const int count = 36;

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
        DWARF,
        WOODELPHS,
        PEGASUS,
        DENDROIDS,
        UNICORN,
        GREENDRAGON,
        FAMILIAR,
        MAGOG,
        CERBERUS,
        HORNEDDEMON,
        PITLORD,
        ENFERNOSULTANO,
        ARCHIDEVIL,
        SKELETWARIOR,
        ZOMBIE,
        GOST,
        WAMPIRE,
        LICHI,
        DARKRYCAR,
        GOSRDRAGON,
        FAIR,
        ELEMENTALER,
        ELEMENTALWATER,
        ELEMENTALFAIR,
        ELEMENTALGRAUND,
        ELEMENTALMAIND,
        FENIX,
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

        void specialAttack();
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
        {heroesClass::CENTAUR, Attributes {5, 7, 0, 0, 3, 8, 3}},
        {heroesClass::DWARF, Attributes {4, 6, 0, 0, 7, 20, 3}},
        {heroesClass::WOODELPHS, Attributes {7, 9, 15, 24, 5, 15, 6}},
        {heroesClass::PEGASUS, Attributes {7, 9, 0, 0, 8, 30, 8}},
        {heroesClass::DENDROIDS, Attributes {8, 9, 0, 0, 9, 55, 3}},
        {heroesClass::UNICORN, Attributes {11, 15, 0, 0, 14, 90, 7}},
        {heroesClass::GREENDRAGON, Attributes {15, 18, 0, 0, 18, 180 , 10}},
        {heroesClass::FAMILIAR, Attributes {2, 4, 0, 0, 4, 4, 7}},
        {heroesClass::MAGOG, Attributes {5, 7, 16, 25, 4, 13, 6}},
        {heroesClass::CERBERUS, Attributes {7, 10, 0, 0, 8, 25, 8}},
        {heroesClass::HORNEDDEMON, Attributes {7, 10, 0, 0, 10, 40, 6}},
        {heroesClass::PITLORD, Attributes {10, 13, 0, 0, 13, 45, 7}},
        {heroesClass::ENFERNOSULTANO, Attributes {13, 16, 0, 0, 14, 90, 13}},
        {heroesClass::ARCHIDEVIL, Attributes {24,26 , 0, 0, 28, 200, 17}},
        {heroesClass::SKELETWARIOR, Attributes {3, 6, 0, 0, 6, 6, 5}},
        {heroesClass::ZOMBIE, Attributes {4, 5, 0, 0, 5, 20, 4}},
        {heroesClass::GOST, Attributes {5, 7, 0, 0, 7, 18, 7}},
        {heroesClass::WAMPIRE, Attributes {7, 12, 0, 0, 10, 42, 9}},
        {heroesClass::LICHI, Attributes {8, 13, 20, 24, 10, 40, 7}},
        {heroesClass::DARKRYCAR, Attributes {13, 18, 0, 0, 18, 120, 9}},
        {heroesClass::GOSRDRAGON, Attributes {18, 30, 0, 0, 17, 200, 14}},
        {heroesClass::FAIR, Attributes {1, 2, 0, 0, 2, 3, 9}},
        {heroesClass::ELEMENTALER, Attributes {7, 9, 20, 24, 9, 25, 8}},
        {heroesClass::ELEMENTALWATER, Attributes {7, 8, 0, 0, 10, 30, 5}},
        {heroesClass::ELEMENTALFAIR, Attributes {10, 12, 0, 0, 8, 35, 8}},
        {heroesClass::ELEMENTALGRAUND, Attributes {10, 11, 0, 0, 11, 40, 6}},
        {heroesClass::ELEMENTALMAIND, Attributes {12, 15, 0, 0, 13, 80, 9}},
        {heroesClass::FENIX, Attributes {17, 21, 0, 0, 18, 200, 21}}
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
        {"∩", heroesClass::CENTAUR},
        {"%", heroesClass::DWARF},
        {"<", heroesClass::WOODELPHS},
        {"&", heroesClass::PEGASUS},
        {"$", heroesClass::DENDROIDS},
        {"*", heroesClass::UNICORN},
        {"@", heroesClass::GREENDRAGON},
        {"^", heroesClass::FAMILIAR},
        {"!", heroesClass::MAGOG},
        {"€", heroesClass::CERBERUS},
        {"Џ", heroesClass::HORNEDDEMON},
        {"Ђ", heroesClass::PITLORD},
        {"•", heroesClass::ENFERNOSULTANO},
        {"ћ", heroesClass::ARCHIDEVIL},
        {"¤", heroesClass::SKELETWARIOR},
        {"§", heroesClass::ZOMBIE},
        {"©", heroesClass::GOST},
        {"±", heroesClass::WAMPIRE},
        {"µ", heroesClass::LICHI},
        {"¶", heroesClass::DARKRYCAR},
        {"Ќ", heroesClass::GOSRDRAGON},
        {"Љ", heroesClass::FAIR},
        {"ѓ",heroesClass::ELEMENTALER},
        {"Њ",heroesClass::ELEMENTALWATER},
        {"{",heroesClass::ELEMENTALFAIR},
        {"„",heroesClass::ELEMENTALGRAUND},
        {"љ",heroesClass::ELEMENTALMAIND},
        {"¦",heroesClass::FENIX},
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
        {heroesClass::CENTAUR, "Centaur"},
        {heroesClass::DWARF,"Dwarf"},
        {heroesClass::WOODELPHS,"WoodElphs"},
        {heroesClass::PEGASUS,"Pegasus"},
        {heroesClass::DENDROIDS,"Dendroids"},
        {heroesClass::UNICORN,"Unicorn"},
        {heroesClass::GREENDRAGON,"GreenDragon"},
        {heroesClass::FAMILIAR,"Familiar"},
        {heroesClass::MAGOG,"Magog"},
        {heroesClass::CERBERUS,"Cerberus"},
        {heroesClass::HORNEDDEMON,"HornedDemon"},
        {heroesClass::PITLORD,"Pitlord"},
        {heroesClass::ENFERNOSULTANO,"EnfernoSultano"},
        {heroesClass::ARCHIDEVIL,"Archidevil"},
        {heroesClass::SKELETWARIOR,"SkeletWarior"},
        {heroesClass::ZOMBIE,"Zombie"},
        {heroesClass::GOST,"Gost"},
        {heroesClass::WAMPIRE,"Wampire"},
        {heroesClass::LICHI,"Lichi"},
        {heroesClass::DARKRYCAR,"DarkKnght"},
        {heroesClass::GOSRDRAGON,"GostDragon"},
        {heroesClass::FAIR,"Fair"},
        {heroesClass::ELEMENTALER,"ElementAir"},
        {heroesClass::ELEMENTALWATER,"ElementWater"},
        {heroesClass::ELEMENTALFAIR,"ElementFire"},
        {heroesClass::ELEMENTALGRAUND,"ElementEarth"},
        {heroesClass::ELEMENTALMAIND,"PsychicElement"},
        {heroesClass::FENIX,"Fenix"}
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

        return " ";
    }
}

#endif 