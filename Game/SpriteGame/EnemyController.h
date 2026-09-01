#pragma once
#include "Framework\Actor.h"

namespace nu {
	class PhysicsComponent;
	class SpriteAnimatorRendererComponent;
}

class EnemyController : public nu::Actor
{
public:
	CLASS_PROTOTYPE(EnemyController)

		void Start() override;
	void Update(float dt) override;

	void OnCollision(nu::Actor* other) override;

	void Read(const nu::json::value_t& value) override;

protected:
	class nu::PhysicsComponent* m_physicsComponent = nullptr;
	class nu::SpriteAnimatorRendererComponent* m_rendererComponent = nullptr;

};

