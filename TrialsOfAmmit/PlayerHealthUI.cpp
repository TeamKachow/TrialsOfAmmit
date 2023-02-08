#include "PlayerHealthUI.h"

PlayerHealthUI::PlayerHealthUI(glm::vec2 spawnPos, Hudson::World::Scene* _scene, Player* _player) : Behaviour("HealthUI")
{
	_currentScene = _scene;
	_currentPos = spawnPos;
	_currentPlayer = _player;
	_playerHealthScale = 3.84;

	

}

PlayerHealthUI::~PlayerHealthUI()
{
}

void PlayerHealthUI::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_healthUISprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("HealthBar"));
	_healthUISprite->SetGridSize(glm::vec2(1, 1));
	_healthUISprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_healthUISprite->SetDepthOrder(30);
	_parent->AddComponent(_healthUISprite);
	_parent->SetName("HealthBar");
	_parent->GetTransform().pos = _currentPos;
	_parent->GetTransform().scale.x = 256;
}

void PlayerHealthUI::OnTick(const double& dt)
{
	
	if (_currentPlayer->_playerHealth <= 0)
	{
		_parent->GetTransform().scale.x = 0;
	}
	else
	{
		_parent->GetTransform().scale.x = _playerHealthScale * _currentPlayer->_playerHealth;
	}
}

void PlayerHealthUI::OnDestroy()
{
}

void PlayerHealthUI::DrawPropertyUI()
{
}
