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

#include <iostream>
#include <vector>

using namespace nu;

void dosomething(std::vector<Vector2>& v) {
    v[0].x = 40.0;
}

int main()
{

    //INITIAL
    Engine engine;

    engine.Initialize();

    
    Mesh mesh{ { Vector2{2, 0}, Vector2{-2, 2}, Vector2{ -1, 0}, Vector2(-2, -2), Vector2(2, 0)}, Color{0.0f, 0.0f, 1.0f}};
    Player player{ 2000.0f, Transform {Vector2 {640.0f, 512.0f}, 0.0f, 15.0f}, std::vector<Mesh>{mesh} };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };

    std::vector<Vector2> points;

    uint64_t ticks = SDL_GetTicks();
    uint64_t prevTicks = ticks;

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

        engine.Update();

        //player.SetRotation(player.GetTransform().rotation +(90.0f * engine.GetTime().GetDeltaTime()));
        player.SetRotation(90.0f);
        player.Update(engine.GetTime().GetDeltaTime());
        
        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty()) {
                points.push_back(engine.GetInput().GetMousePosition());

            }

            Vector2 v = points.back() - engine.GetInput().GetMousePosition();

            if (v.Length() > 10.0f) {
                points.push_back(engine.GetInput().GetMousePosition());
            }
        }

        //undo points
        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Right)) {
            if(points.empty()) points.pop_back();
        }



        //render
        engine.GetRenderer().setColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        //unsigned int (0) - 1 = MAX_NUMBER
                
        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            engine.GetRenderer().setColor(nu::RandomFloat(1.0f), nu::RandomFloat(1.0f), nu::RandomFloat(1.0f));
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
        }

        

        ////character
        player.Draw(engine.GetRenderer());
        
        /*renderer.setColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);*/
        
        engine.GetRenderer().Present();
    }

    //shutdown 

    return 0;
}

