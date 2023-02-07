#pragma once
#include "BaseAbilityClass.h"

class Heal : public BaseAbilityClass
{
public:
	Heal();
	~Heal();
	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)override;

	Player* _player;
	float _healAmount;
	float _currentHealth;

	//maybe i wanna do heal over time or heal per second or instant heal
};

