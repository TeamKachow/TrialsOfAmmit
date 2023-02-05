#pragma once
#include "BaseAbilityClass.h"

class Roll : public BaseAbilityClass
{
public:
	Roll();
	~Roll();

	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactiveAbility(Hudson::World::Scene* _CurrentPassScene);
	Player* _player;
	float _rollSpeed;
	float _defaultSpeed;
};

