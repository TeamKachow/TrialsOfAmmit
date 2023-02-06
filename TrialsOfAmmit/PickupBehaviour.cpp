#include "PickupBehaviour.h"


PickupBehaviour::PickupBehaviour() : Behaviour("Pickup")
{
	std::cout << "Pickup Setup" << "\n";
}

PickupBehaviour::~PickupBehaviour()
{
}

void PickupBehaviour::CheckCollision()
{
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other->GetParent()->GetComponent<PickupWeapon>() != nullptr)
			{
				PickupWeapon* _pickUp = other->GetParent()->GetComponent<PickupWeapon>();
				if (_pickUp != nullptr)
				{
					_currentPlayer->_playersWeapon = _pickUp->_weaponPickup;
					_currentPlayer->_playersWeapon->UpgradeWeapon(_pickUp->_weaponLevel);
					std::cout << "Colliding With Pickup" << "\n";
					collider->ClearColliding();
					_currentScene->RemoveObject(other->GetParent());

					break;
				}
				else
				{
					break;
				}
				break;
			}
			if (other->GetParent()->GetComponent<PickupAbilitys>() != nullptr)
			{
				PickupAbilitys* _pickupAbility= other->GetParent()->GetComponent<PickupAbilitys>();
				if (_pickupAbility != nullptr)
				{
					_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility = _pickupAbility->_abilityPickup;
					collider->ClearColliding();
					_currentScene->RemoveObject(other->GetParent());

					break;
				}

			}

		}
	}
}

void PickupBehaviour::OnCreate()
{
	_currentScene = _parent->GetScene();
	_currentPlayer = _parent->GetComponent<Player>();
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
