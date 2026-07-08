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

#include <iostream>
#include <vector>

using namespace nu;

int main()

{
    //INITIALIZATION
    nu::Renderer renderer;

    renderer.Initialize("Game Engine", 1280, 1024);

    nu::Input input;
    input.Initailize();

    Vector2 position{ 640.0f, 512.0f };
    std::vector<Vector2> points;

    //main loop
    bool quit = false;
    
    while (!quit) {
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

        input.Update();

        uint64_t ticks = SDL_GetTicks(); //1000 ticks per second
        float seconds = ticks / 1000.0f;
        std::cout << seconds << std::endl;

        /*if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";

        if (input.GetButtonPressed(nu::Input::MouseButton::Left)) std::cout << "button pressed\n";
        if (input.GetButtonDown(nu::Input::MouseButton::Left)) std::cout << "button down\n";
        if (input.GetButtonReleased(nu::Input::MouseButton::Left)) std::cout << "button released\n";*/

        if (input.GetButtonDown(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }


        Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -1;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = +1;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -1;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = +1;

        position += velocity;

        //render
        renderer.setColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();
                
        for (size_t i = 0; i < points.size(); i++)
        {
            renderer.setColor(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        //character
        renderer.setColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);
        
        renderer.Present();
    }

    //shutdown 
    renderer.Shutdown();

    return 0;
}

/*for (int i = 0; i < 1000; i++) {
            renderer.setColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1280, rand() % 1280);
             
        }

        renderer.setColor(rand() % 256, rand() % 256, rand() % 256);
        renderer.DrawFillRect(40, 40, 50, 50);*/

        //random points
        // 
        /*for (int i = 0; i < 3; i++) {
            renderer.setColor(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            renderer.DrawFillRect(nu::RandomFloat(1280), nu::RandomFloat(1024), nu::RandomFloat(1280), nu::RandomFloat(1024));
        }*/

        /*for (int i = 0; i < 10; i++) {
                   renderer.setColor(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
                   renderer.DrawLine(nu::RandomFloat(1280), nu::RandomFloat(1024), nu::RandomFloat(1280), nu::RandomFloat(1024));
               }*/