#include "PickupAbilitys.h"
#include <random>

PickupAbilitys::PickupAbilitys(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject) : Behaviour ("AbiltyPickup")
{
	_abilityObject = _refObject;
	_abilityCollider = new Hudson::Physics::ColliderComponent();
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_abilitySprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Abilitys"));
	_abilitySprite->SetSize(glm::vec2(16.0f, 16.0f));
	_abilitySprite->SetGridSize(glm::vec2(2, 1));
	_abilitySprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_abilityObject->AddComponent(_abilitySprite);
	_abilityObject->AddComponent(_abilityCollider);
	_abilityObject->SetName("AbilityPickup");

	_abilitySprite->SetGridPos(glm::vec2(0, 1));
	_abilityObject->GetTransform().pos = spawnPos;
	_randomAbilityInt = 0;
}

PickupAbilitys::~PickupAbilitys()
{
	
}

void PickupAbilitys::OnCreate()
{
	random_device rand;
	uniform_int_distribution<int> dist(0, 2);
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
		_abilityPickup = new Rage;
	}

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
