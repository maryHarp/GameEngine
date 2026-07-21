// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define PS5
//
//#ifdef _DEBUG
//    #define TEXT "PS5\n"
//#else
//#define TEXT "XBOX\n"
//#endif
//
//#define TEXT "hello!\n"
//#define MAX(a, b) ((a > b) ? a : b)

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>

#include <iostream>
#include <vector>

using namespace nu;

void dosomething(std::vector<Vector2>& v) {
    v[0].x = 40.0;
}

int main()
{

    //INITIAL

    engine.Initialize();

    //create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
    
    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("duck-toy.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("oof.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    
    Mesh body{ { Vector2{2, 0}, Vector2{0, 1}, Vector2{ -2, 3}, 
                 Vector2{ -1, 0}, Vector2{ -3, -3}, Vector2{ 0, -1}, Vector2{2, 0}}, Color{ 1.0f, 0.0f, 1.0f }};
    Mesh wings{ { Vector2{1, 3}, Vector2{0, 1}, Vector2{ 0, -1}, Vector2{1, -3}, Vector2{1, 3}}, Color{1.0f, 0.5f, 1.0f} };




    Model model{ std::vector<Mesh>{ body } };
    model.AddMesh(wings);

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2 {640.0f, 512.0f}, 0.0f, 15.0f };
    playerDesc.speed = 2000.0f;
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };

    Player* player = new Player{ playerDesc};
    scene.AddActor(player);
    
    for (int i = 0; i < 20; i++){
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = model;
        enemyDesc.transform = Transform{ Vector2 {nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()),
                                                               nu::RandomFloat((float)nu::engine.GetRenderer().GetHeight())} };
        enemyDesc.speed = 2000.0f;


        Enemy* enemy = new Enemy{ enemyDesc};
        scene.AddActor(enemy);
    }
    
    



    /*Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };*/

    std::vector<Vector2> points;
    
    /*

    uint64_t ticks = SDL_GetTicks();
    uint64_t prevTicks = ticks;*/

    audio->createSound("mario.mp3", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);



    //main loop
    bool quit = false;
    
    while (!quit) {
        audio->update();

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
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

        engine.Update();

        //player.SetRotation(player.GetTransform().rotation +(90.0f * engine.GetTime().GetDeltaTime()));
        /*player.SetRotation(90.0f);*/
        player->Update(engine.GetTime().GetDeltaTime());
        //enemy.Update(engine.GetTime().GetDeltaTime());

        float dt = engine.GetTime().GetDeltaTime();

        scene.Update(dt);


      


        //render
        engine.GetRenderer().setColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();
        
        scene.Draw(engine.GetRenderer());

        
        
        engine.GetRenderer().Present();
    }

    //shutdown 

    return 0;
}

