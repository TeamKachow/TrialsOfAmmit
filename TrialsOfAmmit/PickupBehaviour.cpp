#include "PickupBehaviour.h"
#include "PassivePickups.h"


PickupBehaviour::PickupBehaviour() : Behaviour("Pickup")
{
	std::cout << "Pickup Setup" << "\n";
}

PickupBehaviour::~PickupBehaviour()
{
}

void PickupBehaviour::FromJson(const nlohmann::json& j)
{
}

void PickupBehaviour::ToJson(nlohmann::json& j)
{
}

void PickupBehaviour::CheckCollision()
{
	
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>(); //TODO Make it so it can only Collide Once
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(1);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other != nullptr)
			{
				if (other->GetParent()->GetComponent<PickupWeapon>() != nullptr)
				{
					PickupWeapon* _pickUp = other->GetParent()->GetComponent<PickupWeapon>();
					if (_pickUp != nullptr)
					{
						_currentPlayer->_playersWeapon = _pickUp->_weaponPickup;
						_currentPlayer->_playersWeapon->UpgradeWeapon(_pickUp->_weaponLevel);
						_currentScene->RemoveObject(other->GetParent());
						collider->ClearColliding();
					}

				}
				if (other->GetParent()->GetComponent<PickupAbilitys>() != nullptr)
				{
					PickupAbilitys* _pickupAbility = other->GetParent()->GetComponent<PickupAbilitys>();
					if (_pickupAbility != nullptr)
					{
						_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility = _pickupAbility->_abilityPickup;
						_currentScene->RemoveObject(other->GetParent());
						collider->ClearColliding();
					}
				}
				if (other->GetParent()->GetComponent<PassivePickups>() != nullptr)
				{
					PassivePickups* _pickupPassive = other->GetParent()->GetComponent<PassivePickups>();
					if (_pickupPassive != nullptr)
					{
						switch (_pickupPassive->_passiveType)
						{
						case PT_HEAL:
							_currentPlayer->GetParent()->GetComponent<Player>()->PassiveAddSpeed(10);
						case PT_ATTACK:
							_currentPlayer->GetParent()->GetComponent<Player>()->PassiveAddDamageMod(0.01);
						case PT_SPEED:
							_currentPlayer->GetParent()->GetComponent<Player>()->PassiveAddSpeed(15);
						}
						collider->ClearColliding();
						_currentScene->RemoveObject(other->GetParent());
					}

				}

			}

		}

	}
	
}

void PickupBehaviour::OnCreate()
{
	_currentScene = _parent->GetScene();
	_currentPlayer = _parent->GetComponent<Player>();
	_ThisCollider = new Hudson::Physics::ColliderComponent;
	_parent->AddComponent(_ThisCollider);
}

void PickupBehaviour::OnTick(const double& dt)
{
	if (_inputManager.getActionState("Interact")) //Key Checks
	{
		CheckCollision();


	}
}

void PickupBehaviour::OnDestroy()
{
}

void PickupBehaviour::DrawPropertyUI()
{
}
