#ifndef SOUNDS_H
#define SOUNDS_H

#include <map>
#include <windows.h>
#include <thread>
#include <iostream>
#include "Audio.hpp"

namespace sounds 
{
    std::string path = "sounds/";
    std::map<std::string, sf::Music*> music;

    float volumeEnter = 60.0f;
    float volumeMain = 4.0f;
    float volumeSelect = 4.0f; 
    float volumePage = 80.0f;
    float volumeMoveCursor = 10.0f;
    float volumeBuild = 10.0f;
    float volumeMoveUnit = 20.0f;
    float volumeHurt = 20.0f;
    float volumeKill = 10.0f;

    void load(std::string name, bool loop = false)
    {
        music[name] = new sf::Music();

        if (!music[name]->openFromFile(path + name + ".wav"))
        {
            system("cls");
            std::cout << "ERROR [sounds]";
        }

        music[name]->setLoop(loop);
    }

    void play(std::string name, float volume)
    {
        // std::cout << music[name]->getStatus();
        // Sleep(1000);

        if (music[name]->getStatus() == 0)
        {
            music[name]->stop();
        }

        music[name]->setVolume(volume);
        music[name]->play();
    }

    void stop(std::string name)
    {
        music[name]->stop();
    }
}

#endif