#pragma once
#include <Hudson.h>
class Chest: public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	Chest(glm::vec2 spawnPos);
	~Chest();
	Hudson::Render::SpriteComponent* _chestSprite;
	Hudson::Physics::ColliderComponent* _chestCollider;
	glm::vec2 _spawnPos;
	bool _isOpen;
	void OnInteract();
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};

