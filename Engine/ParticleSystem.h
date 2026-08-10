#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Resource.h"

#include <vector>
#include <memory>



namespace nu {
	class Texture;

	struct Particle
	{
		bool active{ false };
		float lifespan{ 1 };

		Vector2 position{ 0, 0 };
		Vector2 velocity{ 0, 0 };
		Color color{ 0, 0, 0 };
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		bool Initialize(size_t poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();

	private:
		// store particles in particle pool
		res_t<Texture> m_texture;

		Transform m_transform;

		std::vector<Particle> m_particles;
	};

	
}