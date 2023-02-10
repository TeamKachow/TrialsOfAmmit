#pragma once

#include <Hudson.h>
#include "Player.h"

class ShieldMummy : public Hudson::Entity::Behaviour
{
public:
	ShieldMummy(glm::vec2 spawnPos = { 100, 100 });
	~ShieldMummy();

	void Kill();

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;

	Hudson::Entity::GameObject* Blood;
protected:
	Hudson::Render::SpriteComponent* _aiSprite;
	Hudson::Render::SpriteComponent* _aiDeathSprite;
	Hudson::World::Scene* _currentScene;
	Hudson::Physics::ColliderComponent* _aiCollider;
	Player* _player;
	glm::vec2 _spawnPos;
};

