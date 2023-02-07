#include "Rage.h"

Rage::Rage()
{
	_abilityActiveTime = 5;
	_abilityCoolDownTime = 6;
	_abilityState = ready;

	_defaultAttackDamage;
	_defaultAttackSpeed;

	_rageAttackDamage;
	_rageAttackSpeed;

	_rageAttackDamageMultiplier = 2.0f;
	_rageAttackSpeedMultiplier = 1.25f;

	_abilityType = AT_RAGE;
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

			_player->_playerSprite->SetColor(glm::vec3(1, 0, 0)); // make him red

			_defaultAttackDamage =  _player->_playersWeapon->_weaponAttackDamage;
			_rageAttackDamage = _defaultAttackDamage * _rageAttackDamageMultiplier;
			_player->_playersWeapon->_weaponAttackDamage = _rageAttackDamage;
			
			_defaultAttackSpeed = _player->_playersWeapon->_weaponAttackSpeed;
			_rageAttackSpeed = _defaultAttackSpeed * _rageAttackSpeedMultiplier;
			_player->_playersWeapon->_weaponAttackSpeed = _rageAttackSpeed;

			break;
		}
	};

	_abilityState = active;
}

void Rage::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();

			_player->_playerSprite->SetColor(glm::vec3(1, 1, 1)); // unmake him red

			_player->_playersWeapon->_weaponAttackDamage = _defaultAttackDamage;

			_player->_playersWeapon->_weaponAttackSpeed = _defaultAttackSpeed;

			break;
		}
	};

	_abilityState = cooldown;

}
