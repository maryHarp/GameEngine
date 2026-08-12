
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

class Animal {
public:
    virtual void speak() {
        std::cout << "???";
    }
};
class Cat : public Animal {
    void speak() override {
        std::cout << "Meow";
    }
};
class Dog : public Animal {
    void speak() override {
        std::cout << "Bark";
    }
};
class Bird : public Animal {
    void speak() override {
        std::cout << "Chirp";
    }
};

//enum class Type
//{
//    Cat = 1,
//    Dog,
//    Bird
//};
//
//Animal* AnimalFactory(Type id) {
//    Animal* animal = nullptr;
//
//    switch (id)
//    {
//    case Type::Cat: // cat
//        animal = new Cat;
//        break;
//    case Type::Dog:
//        animal = new Dog;
//        break;
//    case Type::Bird:
//        animal = new Bird;
//        break;
//    }
//
//    return animal;
//}

Animal* AnimalFactory(const std::string id) {
    Animal* animal = nullptr;

    if (nu::ToLower(id) == "cat") animal = new Cat;
    else if (nu::EqualsIgnoreCase(id, "Dog")) animal = new Dog;
    else if (nu::ToUpper(id) == "Bird") animal = new Bird;

    return animal;
}

//class ICreator {
//public:
//    virtual ~ICreator() = default;
//    virtual std::unique_ptr<Animal> Create() = 0;
//};
//
//template <typename T>
//
//class Creator : public ICreator {
//    public:
//        std::unique_ptr<Animal> Create() override { return std::make_unique<T>(); }
//};
//
//std::map<std::string, std::unique_ptr<ICreator>> registry;



int main()
{
    nu::SetWorkingDirectory("Assets");

    Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Object>("Object");
    Factory::Instance().Register<Player>("Player");

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
    }




    /*registry["Cat"] = std::make_unique<Creator<Cat>>();
    registry["Dog"] = std::make_unique<Creator<Dog>>();

    auto animal = registry["Dog"]->Create();
    animal->speak();*/

   /* std::string selection;

    std::cout << "Select Animal: ";
    std::cin >> selection;

    auto animal = AnimalFactory(selection);
    if (animal) animal->speak();*/



    return 0; 



    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read the age data (int) from the json
            // read/show the data from the json file
            std::string name;
            int age;
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;

            // read the json data
            nu::json::Read(document, "name", name);
            nu::json::Read(document, "age", age);
            nu::json::Read(document, "speed", speed);
            nu::json::Read(document, "isAwake", isAwake);
            nu::json::Read(document, "position", position);
            nu::json::Read(document, "color", color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
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

