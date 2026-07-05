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
#include "SDL3/SDL.h"


#include <iostream>

int main()
{
    nu::Renderer renderer;

    renderer.Initialize("Game Engine", 1920, 1024);
    

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.setColor(0, 0, 0);
        renderer.Clear();

        /*for (int i = 0; i < 1000; i++) {
            renderer.setColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1280, rand() % 1280);
             
        }

        renderer.setColor(rand() % 256, rand() % 256, rand() % 256);
        renderer.DrawFillRect(40, 40, 50, 50);*/

        //random points
        // 
        for (int i = 0; i < 3; i++) {
            renderer.setColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawFillRect(rand() % 1024, rand() % 1024, rand() % 1024, rand() % 1024);
        }

        for (int i = 0; i < 20; i++)
        {
            renderer.setColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1024, rand() % 1024);
        }

        for (int i = 0; i < 10; i++) {
            renderer.setColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawLine(rand() % 1024, rand() % 1024, rand() % 1024, rand() % 1024);
        }

        
        

        //SDL_SetRenderDrawColor(m_renderer, rand() % 256, rand() % 256, rand() % 256, 255); // Set render draw color to green
        //SDL_RenderFillRect(m_renderer, &greenSquare); // Render the rectangle

        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDebugText(renderer, 30, 30, "Hello World!");

        //SDL_RenderPresent(renderer); // Render the screen
        renderer.Present();

    }

    renderer.Shutdown();

    return 0;
}

