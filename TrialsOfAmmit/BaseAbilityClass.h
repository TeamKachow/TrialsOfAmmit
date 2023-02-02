#pragma once

#include <Hudson.h>
#include "abilityTargets.h"

class BaseAbilityClass : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	//BaseAbilityClass(Hudson::Render::SpriteComponent* _spriteComponent, int cooldown, int active_time /*Target target */);
	//BaseAbilityClass(int cooldown, int active_time);
	BaseAbilityClass();
	~BaseAbilityClass();

	/// <summary>
	/// added the hudson bits cuz i think i'll need em ... eventually
	/// </summary>
	Hudson::World::Scene* _currentScene;
	Hudson::Entity::GameObject* _parent;
	Hudson::Physics::PhysicsComponent* _parentPhysics;
	Hudson::Render::SpriteComponent* _parentSprite;
	Hudson::Physics::ColliderComponent* _parentCollider;
	abilityTargets _abilityTarget;

	std::string _name;
	int _cooldownTime;
	int _activeTime;

	virtual void UseAbility() = 0;
	virtual void UseAbility(Hudson::Entity::GameObject parent) = 0;

protected:
private:
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};





