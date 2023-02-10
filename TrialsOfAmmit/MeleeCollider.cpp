#include "MeleeCollider.h"
#include "AiAgent.h"
#include "Player.h"
#include "Chest.h"
#include "AnubisBoss.h"
#include "LocustBehaviour.h"

MeleeCollider::MeleeCollider(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene, float _damage, bool isAi) : Behaviour("MeleeCollision")
{
	_slashDirection = slashDirection;
	_meleeDamage = _damage;
	_animTimer = 0;
	_animSpeed = 0.2;
	_deleteTime = 0.4;
	_deleteTimer = 0;
	_playerPos = playerPos;
	_currentScene = currentScene;
	_isAI = isAi;

}

MeleeCollider::~MeleeCollider()
{
}

void MeleeCollider::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_slashSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Invis"));
	Hudson::Physics::ColliderComponent* _slashCollider = new Hudson::Physics::ColliderComponent();

	_slashSprite->SetGridSize(glm::vec2(3, 4));
	_slashSprite->SetGridPos(glm::vec2(0, 0));
	_slashSprite->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));

	_parent->AddComponent(_slashSprite);
	_parent->AddComponent(_slashCollider);
	_parent->SetName("SlashCollider");



	switch (_slashDirection) {
	case Down:
		_parent->GetTransform().pos.y = _playerPos.y + 50;
		_parent->GetTransform().pos.x = _playerPos.x;
		break;
	case Left:
		_parent->GetTransform().pos.y = _playerPos.y;
		_parent->GetTransform().pos.x = _playerPos.x - 50;
		break;
	case Right:
		_parent->GetTransform().pos.y = _playerPos.y;
		_parent->GetTransform().pos.x = _playerPos.x + 50;
		break;
	case Up:
		_parent->GetTransform().pos.y = _playerPos.y - 50;
		_parent->GetTransform().pos.x = _playerPos.x;
		break;
	case Stopped:
		_parent->GetTransform().pos.y = _playerPos.y + 50;
		_parent->GetTransform().pos.x = _playerPos.x;
		break;
	default:;
	}
}

void MeleeCollider::OnTick(const double& dt)
{
	if (!_isAI)
	{
		std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
		if (!colliders.empty())
		{
			Hudson::Physics::ColliderComponent* collider = colliders.at(0);
			auto collidingWith = collider->GetCurrentCollisions();
			for (auto other : collidingWith)
			{
				if (other->GetParent()->GetComponent<AiAgent>() != nullptr)
				{
					AiAgent* _aiAgent = other->GetParent()->GetComponent<AiAgent>();
					if (_aiAgent != nullptr)
					{
						_aiAgent->TakeDamage(_meleeDamage);
						std::cout << "Melee Damage : " << _meleeDamage << "\n";

						_currentScene->RemoveObject(_parent);

						break;
					}

				}
				if (other->GetParent()->GetComponent<AnubisBoss>() != nullptr)
				{
					AnubisBoss* _boss = other->GetParent()->GetComponent<AnubisBoss>();
					if (_boss != nullptr)
					{
						_boss->TakeDamage(_meleeDamage);
						_currentScene->RemoveObject(_parent);
						break;
					}
				}
				if (other->GetParent()->GetComponent<LocustBehaviour>() != nullptr)
				{
					LocustBehaviour* _locust = other->GetParent()->GetComponent<LocustBehaviour>();
					if (_locust != nullptr)
					{
						_locust->Kill();
						_currentScene->RemoveObject(_parent);
						break;
					}
				}
				if (other->GetParent()->GetComponent<Chest>() != nullptr)
				{
					Chest* _chest = other->GetParent()->GetComponent<Chest>();
					if (_chest != nullptr)
					{
						_chest->OnInteract();


						break;
					}

				}
				if (other->GetParent()->GetComponent<MeleeCollider>() != nullptr)
				{
					MeleeCollider* enemymeleecollsion = other->GetParent()->GetComponent<MeleeCollider>();
					if (enemymeleecollsion != nullptr)
					{
						break;
					}
					break;
					
				}
				
			}
			collider->ClearColliding();

		}
		_deleteTimer += dt;
		if (_deleteTimer > _deleteTime)
		{
			_currentScene->RemoveObject(_parent);
		}
	}
	else if (_isAI)
	{
		std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
		if (!colliders.empty())
		{
			Hudson::Physics::ColliderComponent* collider = colliders.at(0);
			auto collidingWith = collider->GetCurrentCollisions();
			for (auto other : collidingWith)
			{
				if (other->GetParent()->GetComponent<Player>() != nullptr)
				{
					Player* _player = other->GetParent()->GetComponent<Player>();
					if (_player != nullptr)
					{
						_player->TakeDamage(_meleeDamage);
						std::cout << "Melee Damage : " << _meleeDamage << "\n";
						collider->ClearColliding();
						_currentScene->RemoveObject(_parent);

						break;
					}
					else
					{
						break;
					}
				}
				if (other->GetParent()->GetComponent<MeleeCollider>() != nullptr)
				{
					MeleeCollider* enemymeleecollsion = other->GetParent()->GetComponent<MeleeCollider>();
					if (enemymeleecollsion != nullptr)
					{
						break;
					}
					break;

				}

			}
			collider->ClearColliding();

		}
		_deleteTimer += dt;
		if (_deleteTimer > _deleteTime)
		{
			_currentScene->RemoveObject(_parent);
		}
	}
}

void MeleeCollider::OnDestroy()
{
}

void MeleeCollider::DrawPropertyUI()
{
}

void MeleeCollider::FromJson(const nlohmann::json& j)
{
}

void MeleeCollider::ToJson(nlohmann::json& j)
{
}
