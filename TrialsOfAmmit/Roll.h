#pragma once
#include "BaseAbilityClass.h"


class Roll : public BaseAbilityClass
{
public:
	// Default Methods
	Roll();
	~Roll();
	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactiveAbility(Hudson::World::Scene* _CurrentPassScene)override;

	// Class Variables
	Player* _player;
	float _rollSpeed;
	float _defaultSpeed;
};

