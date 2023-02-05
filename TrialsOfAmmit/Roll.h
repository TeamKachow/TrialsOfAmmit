#pragma once

#include "BaseAbilityClass.h"


class Roll : public BaseAbilityClass
{
public:
	Roll();
	~Roll();

	Player* _player;
	float _rollSpeed;
	void UseAbility(Hudson::World::Scene* _CurrentPassScene, float deltaTime) override;
	//void UseAbility(Hudson::Entity::GameObject*) override;
	void OnCreate() override;
	void OnTick(const double& dt) override;
private:
	
};

