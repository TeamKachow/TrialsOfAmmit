#pragma once
#include <Hudson.h>
class Chest: public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	//Chest(glm::vec2 spawnPos);
	Chest(glm::vec2 spawnPos = { 0,0 });
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

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;
};

