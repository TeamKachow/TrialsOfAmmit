#include "PickupAbilitys.h"
#include <random>

PickupAbilitys::PickupAbilitys(glm::vec2 spawnPos) : Behaviour ("AbiltyPickup")
{
	_spawnPos = spawnPos;
	_randomAbilityInt = 0;
}

PickupAbilitys::~PickupAbilitys()
{

}

void PickupAbilitys::FromJson(const nlohmann::json& j)
{
}

void PickupAbilitys::ToJson(nlohmann::json& j)
{
}

void PickupAbilitys::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_abilitySprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Abilitys"));
	_abilitySprite->SetGridSize(glm::vec2(5, 1));
	_abilitySprite->SetDepthOrder(1);
	_abilitySprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_abilityCollider = new Hudson::Physics::ColliderComponent();

	_parent->AddComponent(_abilitySprite);
	_parent->AddComponent(_abilityCollider);
	_parent->SetName("AbilityPickup");
	_parent->GetTransform().pos = _spawnPos;


	random_device rand;
	uniform_int_distribution<int> dist(0, 5);
	_randomAbilityInt = dist(rand);
	if (_randomAbilityInt == 0)
	{
		_abilitySprite->SetGridPos(glm::vec2(0, 1));
		_abilityPickup = new Roll;
	}
	if (_randomAbilityInt == 1)
	{
		_abilitySprite->SetGridPos(glm::vec2(1, 1));
		_abilityPickup = new Stun;
	}
	if (_randomAbilityInt == 2)
	{
		_abilitySprite->SetGridPos(glm::vec2(2, 1));
		_abilityPickup = new Rage;
	}
	if (_randomAbilityInt == 3)
	{
		_abilitySprite->SetGridPos(glm::vec2(3, 1));
		_abilityPickup = new Heal;
	}
	if (_randomAbilityInt == 4)
	{
		_abilitySprite->SetGridPos(glm::vec2(4, 1));
		_abilityPickup = new RoomAOE;
	}
	/*if (_randomAbilityInt == 5)
	{
		_abilitySprite->SetGridPos(glm::vec2(5, 1));
		_abilityPickup = new OneUP;
	}*/

}

void PickupAbilitys::OnTick(const double& dt)
{
}

void PickupAbilitys::OnDestroy()
{
}

void PickupAbilitys::DrawPropertyUI()
{
}
