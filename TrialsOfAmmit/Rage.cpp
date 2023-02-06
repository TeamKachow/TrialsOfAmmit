#include "Rage.h"

Rage::Rage()
{
	_abilityActiveTime = 5;
	_abilityCoolDownTime = 5;
	_abilityState = ready;

	_defaultAttackDamage;
	_defaultAttackSpeed;

	_rageAttackDamage;
	_rageAttackSpeed;

	_rageAttackDamageMultiplier = 2.0f;
	_rageAttackSpeedMultiplier = 1.25f;
}

Rage::~Rage()
{

}

void Rage::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();

			/*
			_rageAttackDamage = _defaultAttackDamage * _rageAttackDamageMultiplier;
			_player->_playersWeapon->_weaponAttackDamage = _rageAttackDamage;

			_rageAttackSpeed = _defaultAttackSpeed * _rageAttackSpeedMultiplier;
			_player->_playersWeapon->_weaponAttackSpeed = _rageAttackSpeed;
			*/

			/*
			*/
			_defaultAttackDamage =  _player->_playersWeapon->_weaponAttackDamage;
			_rageAttackDamage = _defaultAttackDamage * _rageAttackDamageMultiplier;
			_player->_playersWeapon->_weaponAttackDamage = _rageAttackDamage;
			
			_defaultAttackSpeed = _player->_playersWeapon->_weaponAttackSpeed;
			_rageAttackSpeed = _defaultAttackSpeed * _rageAttackSpeedMultiplier;
			_player->_playersWeapon->_weaponAttackSpeed = _rageAttackSpeed;


			break;
		}
	};
}

void Rage::DeactiveAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();

			_player->_playersWeapon->_weaponAttackDamage = _defaultAttackDamage;

			_player->_playersWeapon->_weaponAttackSpeed = _defaultAttackSpeed;

			break;
		}
	};
}
