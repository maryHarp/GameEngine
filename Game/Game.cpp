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



    //std::cout << sizeof(Vector2) << std::endl;

    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> v;

    for (int i = 0; i < 300; i++) {

        v.push_back(Vector2{ nu::RandomFloat(1080), nu::RandomFloat(1024) });
    }
    
    //main loop
    bool quit = false;
    
    while (!quit) {
        //update
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }


        }

        //render
        renderer.setColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

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

        for (size_t i = 0; i < v.size(); i++)
        {
            renderer.setColor(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            v[i] = v[i] + vel;

            renderer.DrawPoint(v[i].x, v[i].y);
        }

        /*for (int i = 0; i < 10; i++) {
            renderer.setColor(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            renderer.DrawLine(nu::RandomFloat(1280), nu::RandomFloat(1024), nu::RandomFloat(1280), nu::RandomFloat(1024));
        }*/

        
      
        renderer.Present();

    }

    //shutdown 
    renderer.Shutdown();

    return 0;
}

