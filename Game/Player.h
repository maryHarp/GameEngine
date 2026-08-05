#pragma once
#include "Actor.h"



struct PlayerDesc : public nu::ActorDesc {
    float speed = 0.0f;

};

class Player : public nu::Actor{
public:
    Player() = default;
    Player(const PlayerDesc& playerDesc) :
        Actor{ playerDesc },
        m_speed{ playerDesc.speed }

    {}


    void Update(float dt) override;
    
    void OnCollision(Actor* other)override;

    bool IsInvincible() const { return m_invinibleTimer > 0.0f; }

private:
    float m_speed = 4000.0f;
    float m_invinibleTimer = 1.0f;
    float m_invinibleDuration = 2.0f;



    

};