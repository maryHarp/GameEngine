#include "SpriteGame.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"
#include <memory>
#include "Framework/Scene.h"


using namespace nu;
class Scene;

bool SpriteGame::Initialize() {

	SetWorkingDirectory("SpriteGame"); 

	Game::Initialize();

	m_scene = std::make_unique<nu::Scene>();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");


	m_titleText = new Text(Resources().Get<Font>("fonts/font.ttf", 50.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "AstroBlast", Color{ 1, 1, 1 });

	m_gameText = new Text(Resources().Get<Font>("fonts/font.ttf", 10.0f));

	m_gameOverText = new Text(Resources().Get<Font>("fonts/font.ttf", 50.0f));

	//Engine::Get().GetAudio().AddSound("alert", "audio/alert.mp3");

	return true;
}


void SpriteGame::Update(float dt){
	switch (m_gameState) 
	{
	case SpriteGame::Title:
		//draw title

		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = SpriteGame::StartGame;
		}
		break;
	case SpriteGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_enemiesToSpawn = 5;
		m_enemiesLeft = 5;
		m_round = 1;
		m_spawnTimer = 5.0f;
		m_stateTimer = 0.5f;
		m_gameState = SpriteGame::StartLevel;
		break;
	case SpriteGame::StartLevel:
		m_scene->RemoveAllActors();
		SpawnPlayer();
		m_enemiesLeft = m_enemiesToSpawn;
		SpawnEnemy(m_enemiesToSpawn);

		
		m_gameState = SpriteGame::Game;
		break;
		
	case SpriteGame::Game:
		//draw score / lives
		
			if (m_enemiesLeft == 0) {
				if (m_round < m_maxRounds) {
					m_round++;
					m_enemiesToSpawn += 2;
					m_enemiesLeft = m_enemiesToSpawn;
					m_gameState = SpriteGame::StartLevel;
				}


				else {
					m_gameState = SpriteGame::Win;
				}


			}



		break;
	case SpriteGame::GameOver:
		//draw game over
		if (m_stateTimer <= 0) {
			m_scene->RemoveAllActors();


		}
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = SpriteGame::Title;
		}

		break;
	case SpriteGame::Win:
		//draw game over
		if (m_stateTimer <= 0) {
			m_scene->RemoveAllActors();

		}
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = SpriteGame::Title;
		}

		break;

	}
	Game::Update(dt);
}

void SpriteGame::Draw(nu::Renderer& renderer) {
	renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/background.png", Engine::Get().GetRenderer()), 500, 500, 0, 5.0f);
	switch (m_gameState)
	{
	case SpriteGame::Title:
		m_titleText->Draw(renderer, 450, 450);
		break;
	case SpriteGame::StartGame:
		break;
	case SpriteGame::StartLevel:

		break;
	case SpriteGame::Game:
		m_gameText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_gameText->Draw(renderer, 30, 30);
		m_gameText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_gameText->Draw(renderer, 30, 60);
		m_gameText->Create(renderer, "Round: " + std::to_string(m_round) + " / " + std::to_string(m_maxRounds), {1.0f, 1.0f, 1.0f});
		m_gameText->Draw(renderer, 30, 90);
		break;
	case SpriteGame::GameOver:
		m_gameOverText->Create(renderer, "GAME OVER", { 1.0f, 0.0f, 0.0f });
		m_gameOverText->Draw(renderer, 450, 450);
		break;
	case SpriteGame::Win:
		m_gameOverText->Create(renderer, "YOU WIN!", { 0.0f, 1.0f, 0.0f });
		m_gameOverText->Draw(renderer, 450, 450);
		break;
	default:
		break;

	}

	Game::Draw(renderer);
}

void SpriteGame::OnPlayerDead()


{

	m_lives--;
	if (m_lives == 0) {
		m_gameState = SpriteGame::GameOver;
	}
	else {
		m_gameState = SpriteGame::StartLevel;
	}

}

void SpriteGame::SpawnPlayer() {
	//auto actor = Factory::Instance().Create<Player>("PlayerPrototype");


	//m_scene->AddActor(std::move(actor));
	


}

void SpriteGame::SpawnEnemy(int count)
{
	for (int i = 0; i < count; i++) {

		//auto actor = Factory::Instance().Create<Enemy>("EnemyPrototype");


		//m_scene->AddActor(std::move(actor));

		//EnemyDesc enemyDesc;
		//enemyDesc.name = "Enemy";
		//enemyDesc.tag = "Enemy";
		////enemyDesc.model = assets::enemyModel;
		//enemyDesc.texture = Resources().Get<Texture>("textures/enemy.png", Engine::Get().GetRenderer());
		//enemyDesc.transform = Transform{ Vector2 {nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()),
		//													   nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 0.0f, 1.0f };
		//enemyDesc.speed = 500.0f;
		//enemyDesc.damping = 3.0f;


		//m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
	}



}
