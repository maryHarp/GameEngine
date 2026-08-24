
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Renderer/Texture.h"
#include "Bullet.h"


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
    SetWorkingDirectory("Assets");

   /* 

    auto actor = Factory::Instance().Create<Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;

    auto object = Factory::Instance().Create("Object");
    std::cout << object->IsActive() << std::endl;

    auto player = Factory::Instance().Create<Player>("Player");
    std::cout << player->IsActive() << std::endl;

    json::document_t document;
    if (json::Load("data/scene.json", document)) {
        player->Read(document);
        std::cout << player->GetName() << std::endl;
        std::cout << player->GetTag() << std::endl;

        std::cout << player->GetTransform().rotation << std::endl;
        std::cout << player->GetSpeed() << std::endl;
    }*/

   
   
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

