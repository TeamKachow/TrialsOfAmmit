#pragma once
#include "BaseAbilityClass.h"

class Rage : public BaseAbilityClass
{
public:
	Rage();
	~Rage();
	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactiveAbility(Hudson::World::Scene* _CurrentPassScene)override;

	Player* _player;
	float _defaultAttackDamage;
	float _defaultAttackSpeed;
	float _rageAttackDamage;
	float _rageAttackSpeed;
	float _rageAttackDamageMultiplier;
	float _rageAttackSpeedMultiplier;
};

