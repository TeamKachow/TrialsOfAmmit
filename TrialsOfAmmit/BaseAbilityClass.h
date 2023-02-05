#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <Hudson.h>
#include "abilityTargets.h"
#include "Player.h"

class BaseAbilityClass : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	//BaseAbilityClass(Hudson::Render::SpriteComponent* _spriteComponent, int cooldown, int active_time /*Target target */);
	//BaseAbilityClass(int cooldown, int active_time);
	BaseAbilityClass();
	~BaseAbilityClass();
	//Hudson::World::Scene* _currentScene;
	//Hudson::Entity::GameObject* _parentGO;
	Hudson::Physics::PhysicsComponent* _parentPhysics;
	Hudson::Render::SpriteComponent* _parentSprite;
	Hudson::Physics::ColliderComponent* _parentCollider;
	Hudson::World::Scene* _currentscene;
	abilityTargets _abilityTarget;
	std::string _name;
	int _cooldownTime;
	int _activeTime;
	virtual void UseAbility(Hudson::World::Scene* _CurrentPassScene, float deltaTime);

protected:


private:
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};





