
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Texture.h"


#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>
#include <fstream>


using namespace nu;


int main()
{
    nu::SetWorkingDirectory("Assets");

    {
        //read file (input file)
        std::ifstream file("data/text.txt");
        if (file.is_open()) {
            std::string str;
            while (std::getline(file, str)) {
                std::cout << str << std::endl;
            }
        }
        else {
            std::cout << "Could not load: data/text.txt\n";
        }
        //file.close(); closes manually out of cope but you can close it like this
    }

    {
        //write file (output file)
        std::ofstream file("data/text.txt", std::ios::app);
        if (file.is_open()) {
            file << "Have a good day!\n";
        }
    }

    {
        //read / write (input/output)
        std::fstream file("data/text.txt", std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open()) 
        {
            //input
            file << "Add a line\n";
            file.seekg(0);
            //output
            std::string str;
            while (std::getline(file, str)) {
                std::cout << str << std::endl;
            }
        }
    }

    {
        std::string name;
        int score;
        bool isAlive;

        //save game data
        bool save = false;
        if (save) {
            name = "Mary";
            score = 420;
            isAlive = true;

            //save game data
            std::ofstream file("data/game.txt");
            if (file.is_open()) {
                file << name <<"\n";
                file << score << "\n";
                file << std::boolalpha << isAlive << "\n";
            }
        }

        //load game data
        bool load = true;
        if (load) {
            //read file
            std::ifstream file("data/game.txt");
            if (file.is_open()) {
                std::getline(file, name);

                std::string str;
                std::getline(file, str);

                score = std::stoi(str);
                //file >> score;
                file >> std::boolalpha >> isAlive;

            }
        }

        //display game data
        std::cout << name << std::endl;
        std::cout << score << std::endl;
        std::cout << isAlive << std::endl;
    }

    return 0;
   
    //INITIAL

    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    //create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
    
    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
   
    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("bgmusic.mp3", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);

    //main loop
    bool quit = false;
    
    while (!quit) {
        audio->update();

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        //update
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }

        }

        Engine::Get().Update();
   
        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);

        //render
        Engine::Get().GetRenderer().setColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();
        
        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }

    //shutdown 
    Engine::Get().Shutdown();

    return 0;
}

