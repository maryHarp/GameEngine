#include "pch.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Bullet.h"
#include "Renderer/Model.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Resources/ResourceManager.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
    
    //invincibility 
    if (m_invinibleTimer > 0.0f) {
        m_invinibleTimer -= dt;
    }

    //movement
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        thrust = m_speed;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) {
        thrust = -m_speed;
    }

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{1, 0}; // -> 
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    if (thrust) {
        nu::Particle particle;
        particle.position = m_transform.position;
        //particle.color = { 1.0f, 1.0f, 1.0f };
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
        particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

        nu::Engine::Get().GetPS().AddParticle(particle);
    }


    

    //fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {

        auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet->SetTransform(m_transform);
        bullet->SetScale(2.0f);
        bullet->SetTag("PlayerBullet");

        m_scene->AddActor(std::move(bullet));

        /*BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "PlayerBullet";
        desc.texture = nu::Resources().Get<nu::Texture>("textures/bullet.png", nu::Engine::Get().GetRenderer());
        desc.transform = m_transform;
        desc.transform.scale = 1.0f;
        desc.speed = 1000.0f;
        desc.lifespan = 1.0f;
     


        m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));


        if (((SpaceGame*)m_scene->GetGame())->GetScore() >= 3000) {
            desc.transform.rotation += 20.0f;
            m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));


            desc.transform.rotation -= 40.0f;
            m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

        }*/

        
    }

    //bullet time
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }



    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (IsInvincible()) {
        return;
    }


    if (other->GetTag() == "Enemy") {
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
}

void Player::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}
