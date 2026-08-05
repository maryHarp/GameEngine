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
#include "Assets.h"
#include "SpaceGame.h"
#include "Texture.h"


#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>
#include <memory>



using namespace nu;

class Object {
public: 
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { 
        std::cout << "assignment\n"; 
        return *this; 
    }
};

int main()
{
    std::cout << "==================object=================\n";
    

    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;

    }
    std::cout << "==================raw pointers=================\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA); 
        std::cout << objectB << std::endl;
        Object* objectC =  nullptr; 
        objectC = objectA;
        std::cout << objectC << std::endl;
        
        delete objectA;
        delete objectB;
        //delete objectC;

    }
    std::cout << "==================unique pointers=================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA); 
        //std::cout << objectA.get() << std::endl; // the 'guts' are ripped out and given to B
        std::cout << objectB.get() << std::endl;

        objectB.reset();


    }

    std::cout << "==================shared pointers=================\n";
    std::shared_ptr<Object> objectC;
    {
        //std::shared_ptr<Object> objectA = std::make_shared<Object>();
        auto objectA = std::make_shared<Object>();
        std::cout << objectA.get() << std::endl;
        std::cout << objectA.use_count() << std::endl;
        auto objectB = objectA;
        std::cout << objectB.get() << std::endl;
        std::cout << objectB.use_count() << std::endl;
        objectC = objectA;
        std::cout << objectC.get() << std::endl;
        std::cout << objectC.use_count() << std::endl;
    }
    std::cout << objectC.use_count() << std::endl;

    //returns program w/o everything else
    //return 0;

    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    
    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    //INITIAL

    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("textures/SpaceCat.png", Engine::Get().GetRenderer());




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

        //player.SetRotation(player.GetTransform().rotation +(90.0f * Engine::Get().GetTime().GetDeltaTime()));
        /*player.SetRotation(90.0f);*/
        //enemy.Update(Engine::Get().GetTime().GetDeltaTime());

        float dt = Engine::Get().GetTime().GetDeltaTime();

        

        game.Update(dt);
      


        //render
        Engine::Get().GetRenderer().setColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();
        
        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        // TODO:: get engine renderer.DrawTexture(...get() texture pointer..., 30, 30);
        Engine::Get().GetRenderer().DrawTexture(texture.get(), 30.0f, 30.0f);
        
        Engine::Get().GetRenderer().Present();
    }

    //shutdown 
    Engine::Get().Shutdown();

    return 0;
}

