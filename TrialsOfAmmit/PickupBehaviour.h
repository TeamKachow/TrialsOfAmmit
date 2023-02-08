#pragma once
#include <Hudson.h>
#include "PickupWeapon.h"
#include "PickupAbilitys.h"
#include "Player.h"

class PickupBehaviour : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PickupBehaviour();
	~PickupBehaviour();
	Hudson::Input::InputManager _inputManager;
	Hudson::World::Scene* _currentScene;
	Hudson::Physics::ColliderComponent* _ThisCollider;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	Player* _currentPlayer;
	void CheckCollision();
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};

