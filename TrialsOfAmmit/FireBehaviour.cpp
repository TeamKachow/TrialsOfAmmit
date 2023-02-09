#include "FireBehaviour.h"

FireBehaviour::FireBehaviour(glm::vec2 spawnPos) : Behaviour("FireBehaviour")
{
	_spawnPos = spawnPos;
}

FireBehaviour::~FireBehaviour()
{

}

void FireBehaviour::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	FireSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Fire"));
	FireSprite->SetGridSize(glm::vec2(3, 1));
	FireSprite->SetGridPos(glm::vec2(0, 0));
	CollisionBox = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(CollisionBox);
	FireSprite->SetDepthOrder(20);
	_parent->AddComponent(FireSprite);
	_parent->GetTransform().pos = _spawnPos;
	_currentScene = _parent->GetScene();
	_currentState = IGNITE;
}

void FireBehaviour::OnDestroy()
{
}

void FireBehaviour::OnTick(const double& dt)
{
	switch (_currentState)
	{
	case IGNITE:
	{
		_igniteTimer += dt;
		if (_igniteTimer >= 1.0)
		{
			FireSprite->SetGridPos(glm::vec2(2, 0));
			_currentState = BURN;
		}
		else if (_igniteTimer >= 0.5)
		{
			FireSprite->SetGridPos(glm::vec2(1, 0));
		}
		break;
	}
	case BURN:
	{
		if (_BurnTimer >= 0.5)
		{
			_currentState = EXTINGUISH;

		}
		_BurnTimer += dt;
		std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
		if (!colliders.empty())
		{
			Hudson::Physics::ColliderComponent* collider = colliders.at(0);
			auto collidingWith = collider->GetCurrentCollisions();
			for (auto other : collidingWith)
			{
				if (other->GetParent()->GetComponent<Player>() != nullptr)
				{
					Player* player = other->GetParent()->GetComponent<Player>();
					if (player != nullptr)
					{
						player->TakeDamage(25.0f);
						_currentState = EXTINGUISH;
						break;
					}
				}
			}
			collider->ClearColliding();
		}
		break;
	}
	case EXTINGUISH:
	{
		_currentScene->RemoveObject(_parent);
		break;
	}
	}
}

void FireBehaviour::FromJson(const nlohmann::json& j)
{
}

void FireBehaviour::ToJson(nlohmann::json& j)
{
}
