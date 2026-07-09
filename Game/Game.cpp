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

struct Transform {
    Vector2 position;
    float rotation;
    float scale;
};

class Actor {
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform { transform } {}

    void Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.987f;

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const Renderer& renderer) const {
        renderer.setColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const { return m_transform; }
    void SetPosition(const Vector2& position) { m_transform.position = position; }
    void SetRotation(float rotation) { m_transform.rotation = rotation; }
    void SetScale(float scale) { m_transform.rotation = scale; }

    const Vector2 GetVelocity() const{ return m_velocity; }
    void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }


protected:
    Transform m_transform;
    Vector2 m_velocity{ 0,0 };

};



int main()

{
    //INITIALIZATION
    nu::Renderer renderer;

    renderer.Initialize("Game Engine", 1280, 1024);

    nu::Input input;
    input.Initailize();

    nu::Time time;

    Actor player{ Transform{ Vector2{640.0f, 512.0f}, 0.0f, 50.0f} };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 200.0f;

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

        input.Update();
        time.Tick();

        /*if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";

        if (input.GetButtonPressed(nu::Input::MouseButton::Left)) std::cout << "button pressed\n";
        if (input.GetButtonDown(nu::Input::MouseButton::Left)) std::cout << "button down\n";
        if (input.GetButtonReleased(nu::Input::MouseButton::Left)) std::cout << "button released\n";*/

        /*if (input.GetButtonPressed(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }*/
        if (input.GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty()) {
                points.push_back(input.GetMousePosition());

            }

            Vector2 v = points.back() - input.GetMousePosition();

            if (v.Length() > 10.0f) {
                points.push_back(input.GetMousePosition());
            }
        }

        //undo points
        if (input.GetButtonPressed(Input::MouseButton::Right)) {
            if(points.empty()) points.pop_back();
        }


        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        /*velocity += (force * time.GetDeltaTime());
        position += (velocity * time.GetDeltaTime());

        position.x = Wrap(0.0f, 1280.0f, position.x);
        position.y = Wrap(0.0f, 1024.0f, position.y);*/


        //render
        renderer.setColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        //unsigned int (0) - 1 = MAX_NUMBER
                
        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            renderer.setColor(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            renderer.DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
        }

        ////character
        player.Draw(renderer);
        
        //renderer.setColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);
        
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