#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "ResourceManager.h"

#include <memory>

using namespace nu;
class Scene;

bool SpaceGame::Initialize() {
	Game::Initialize();

	m_scene = new nu::Scene();
	m_scene->SetGame(this);

	//m_titleFont->Load("fonts/font.ttf", 100);

	//Resources().Get<Font>("fonts/font.ttf", 100);
	//Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer());


	m_titleText = new Text(Resources().Get<Font>("fonts/font.ttf", 100));
	m_titleText->Create(Engine::Get().GetRenderer(), "AstroBlast", Color{ 1, 1, 1 });

	m_scoreText = new Text(Resources().Get<Font>("fonts/font.ttf", 32));
	m_livesText = new Text(Resources().Get<Font>("fonts/font.ttf", 32));
	m_roundsText = new Text(Resources().Get<Font>("fonts/font.ttf", 32));
	


	m_gameOverFont = std::make_shared<Font>();
	m_gameOverFont->Load("fonts/font.ttf", 100);

	m_gameOverText = new Text(m_gameOverFont);

	//Engine::Get().GetAudio().AddSound("alert", "audio/alert.mp3");

	return true;
}


void SpaceGame::Update(float dt){
	switch (m_gameState) 
	{
	case SpaceGame::Title:
		//draw title

		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = SpaceGame::StartGame;
		}
		break;
	case SpaceGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_enemiesToSpawn = 5;
		m_enemiesLeft = 5;
		m_round = 1;
		m_spawnTimer = 5.0f;
		m_stateTimer = 0.5f;
		m_gameState = SpaceGame::StartLevel;
		break;
	case SpaceGame::StartLevel:
		m_scene->RemoveAllActors();
		SpawnPlayer();
		m_enemiesLeft = m_enemiesToSpawn;
		SpawnEnemy(m_enemiesToSpawn);

		
		m_gameState = SpaceGame::Game;
		break;
		
	case SpaceGame::Game:
		//draw score / lives
		
			if (m_enemiesLeft == 0) {
				if (m_round < m_maxRounds) {
					m_round++;
					m_enemiesToSpawn += 2;
					m_enemiesLeft = m_enemiesToSpawn;
					m_gameState = SpaceGame::StartLevel;
				}


				else {
					m_gameState = SpaceGame::Win;
				}


			}



		break;
	case SpaceGame::GameOver:
		//draw game over
		if (m_stateTimer <= 0) {
			m_scene->RemoveAllActors();

			

		}
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = SpaceGame::Title;
		}

		break;
	case SpaceGame::Win:
		//draw game over
		if (m_stateTimer <= 0) {
			m_scene->RemoveAllActors();

			

		}
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = SpaceGame::Title;
		}

		break;

	}
	Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer) {
	switch (m_gameState)
	{
	case SpaceGame::Title:
		m_titleText->Draw(renderer, 325, 450);
		break;
	case SpaceGame::StartGame:
		break;
	case SpaceGame::StartLevel:

		break;
	case SpaceGame::Game:
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30, 30);
		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, 30, 60);
		m_roundsText->Create(renderer, "Round: " + std::to_string(m_round) + " / " + std::to_string(m_maxRounds), {1.0f, 1.0f, 1.0f});
		m_roundsText->Draw(renderer, 30, 90);
		break;
	case SpaceGame::GameOver:
		m_gameOverText->Create(renderer, "GAME OVER", { 1.0f, 0.0f, 0.0f });
		m_gameOverText->Draw(renderer, 325, 450);
		break;
	case SpaceGame::Win:
		m_gameOverText->Create(renderer, "YOU WIN!", { 0.0f, 1.0f, 0.0f });
		m_gameOverText->Draw(renderer, 325, 450);
		break;
	default:
		break;

	}

	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()


{

	m_lives--;
	if (m_lives == 0) {
		m_gameState = SpaceGame::GameOver;
	}
	else {
		m_gameState = SpaceGame::StartLevel;
	}

}

void SpaceGame::SpawnPlayer() {
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.model = assets::playerModel;
	playerDesc.transform = Transform{ Vector2 {640.0f, 512.0f}, 0.0f, 15.0f };
	playerDesc.speed = 2000.0f;
	playerDesc.velocity = Vector2{ 0.0f, 0.0f };
	playerDesc.damping = 3.0f;

	std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy(int count)
{
	for (int i = 0; i < count; i++) {
		EnemyDesc enemyDesc;
		enemyDesc.name = "Enemy";
		enemyDesc.model = assets::enemyModel;
		enemyDesc.transform = Transform{ Vector2 {nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()),
															   nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 0.0f, 15.0f };
		enemyDesc.speed = 500.0f;
		enemyDesc.damping = 3.0f;


		m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
	}



}
