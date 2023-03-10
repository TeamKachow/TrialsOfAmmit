#include "Heal.h"

Heal::Heal()
{
	_abilityActiveTime = 1;
	_abilityCoolDownTime = 7;
	_abilityState = ready;

	_healAmount = 20;
	_currentHealth;
	_abilityType = AT_HEAL;
}

Heal::~Heal()
{

}

void Heal::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>(); // wanna try make it per second?

			if (_player->_playerHealth < _player->_maxHealth)
			{
				_player->_playerHealth += _healAmount; // need to make it so it doesnt go over max health which is 100
				_player->_playerSprite->SetColor(glm::vec3(0, 1, 0));
			}

			_currentHealth = _player->_playerHealth;

			break;
		}
	};

	_abilityState = active;
}

void Heal::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player->_playerSprite->SetColor(glm::vec3(1, 1, 1));
			break;
		}
	};

	_abilityState = cooldown;
}
