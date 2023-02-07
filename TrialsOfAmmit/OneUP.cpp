#include "OneUP.h"

OneUP::OneUP()
{
	_abilityActiveTime = 10;
	_abilityCoolDownTime = 50;
	_abilityState = ready;

	_healthRegained = 0.5; // as in 50%
	_playerDead = false;
	_hasBeenUsed = false;
}

OneUP::~OneUP()
{
}

void OneUP::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			// INSERT CODE HERE . . .
			if (_player->_playerHealth < 1)
			{
				_playerDead = true;
			}
			/*else
			{
				_abilityState = ready;
			}*/

			if (_playerDead)
			{
				_player->_playerHealth = _player->_maxHealth * _healthRegained;
				DeactivateAbility(_CurrentPassScene);
			}

			break;
		}
	};

	_abilityState = active;
}

void OneUP::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			// INSERT CODE HERE . . .

			break;
		}
	};

	_abilityState = cooldown;
}
/*
OneUP::OneUP()
{
	_abilityActiveTime = 10;
	_abilityCoolDownTime = 50;
	_abilityState = ready;
}

OneUP::~OneUP()
{
}

void OneUP::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			// INSERT CODE HERE . . .

			break;
		}
	};

	_abilityState = active;
}

void OneUP::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			// INSERT CODE HERE . . .

			break;
		}
	};

	_abilityState = cooldown;
}
*/
