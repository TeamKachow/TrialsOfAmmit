#pragma once
#include "BaseAbilityClass.h"

class OneUP : public BaseAbilityClass
{
public:
	OneUP();
	~OneUP();
	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactivateAbility(Hudson::World::Scene* _CurrentPassScene) override;

	Player* _player;
	bool _hasBeenUsed;
	bool _playerDead;
	float _healthRegained;
	float _healthThreshold;

	// make a simple phoenix ult - run it back?
	// make a second chance thing like in hades?
};

