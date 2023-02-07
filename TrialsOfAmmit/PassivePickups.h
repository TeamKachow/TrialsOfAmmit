#pragma once
#include <Hudson.h>
#include "PassiveType.h"

class PassivePickups : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PassivePickups(glm::vec2 _spawnpos);
	~PassivePickups();
	Hudson::Render::SpriteComponent* _passiveSprite;
	Hudson::Physics::ColliderComponent* _passiveCollider;
	glm::vec2 _spawnPos;

	PassiveTypes _passiveType;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	int _randomPassiveInt;


};

