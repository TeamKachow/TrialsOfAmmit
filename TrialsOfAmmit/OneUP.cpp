#include "OneUP.h"

OneUP::OneUP()
{
	_abilityActiveTime = 10;
	_abilityCoolDownTime = 5;
	_abilityState = ready;

	_healthRegained = 0.5; // as in 50%
	_healthThreshold = 60;
	_playerDead = false;
	_hasBeenUsed = false;
}

OneUP::~OneUP()
{
}

//void OneUP::UseAbility(Hudson::World::Scene* _CurrentPassScene)
//{
//	Hudson::World::Scene* _currentScene;
//	_currentScene = _CurrentPassScene;
//	auto _sceneObjects = _currentScene->GetObjects();
//	for (Hudson::Entity::GameObject* other : _sceneObjects)
//	{
//		if (other->GetName() == "Player")
//		{
//
//			std::cout << " Ability OneUP is active ! \n" ;
//			
//			/*_player = other->GetComponent<Player>();
//			if (_player->_playerHealth < 30)
//			{
//				std::cout << " Player is gon die !!! \n";
//				_playerDead = true;
//			}*/
//
//			/*if (_playerDead)
//			{
//				std::cout << " Ability OneUP is activated !!! \n";
//				_player->_playerHealth = _player->_maxHealth * _healthRegained;
//				DeactivateAbility(_CurrentPassScene);
//			}*/
//			
//			if (_player->_playerHealth < 60)
//			{
//				_playerDead = true;
//
//				if (_playerDead)
//				{
//					std::cout << " Ability OneUP is activated !!! \n";
//					_player->_playerHealth = _player->_maxHealth * _healthRegained;
//					DeactivateAbility(_CurrentPassScene);
//				}
//			}
//
//			break;
//		}
//	};
//	//std::cout << " Ability OneUP is active ! \n" ;
//	_abilityState = active;
//}

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

			//_abilityState = active;

			//std::cout << " Ability OneUP is active ! \n";

			while (_abilityState = active)
			{
				std::cout << " Ability OneUP is active ! \n";

				if (_player->_playerHealth < _healthThreshold)
				{
					_playerDead = true;

					if (_playerDead)
					{
						std::cout << " Ability OneUP is activated !!! \n";
						_player->_playerHealth = _player->_maxHealth * _healthRegained;
						DeactivateAbility(_CurrentPassScene);
					}
				}
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

