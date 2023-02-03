#include "MeleeCollider.h"
#include "AiAgent.h"

MeleeCollider::MeleeCollider(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene, Hudson::Entity::GameObject* _slashRef) : Behaviour("MeleeCollision")
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_slashSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Invis"));
	Hudson::Physics::ColliderComponent* _slashCollider = new Hudson::Physics::ColliderComponent();

	_slashSprite->SetGridSize(glm::vec2(3, 4));
	_slashSprite->SetGridPos(glm::vec2(0, 0));
	_slashSprite->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));

	_slash = _slashRef;

	_slash->AddComponent(_slashSprite);
	_slash->AddComponent(_slashCollider);

	_slash->SetName("SlashCollider");

	_slashDirection = slashDirection;

	_animTimer = 0;
	_animSpeed = 0.2;

	_deleteTime = 0.4;
	_deleteTimer = 0;

	_playerPos = playerPos;

	_currentScene = currentScene;
	_currentScene->AddObject(_slash);
}

MeleeCollider::~MeleeCollider()
{
}

void MeleeCollider::OnCreate()
{
	switch (_slashDirection) {
	case Down:
		_slash->GetTransform().pos.y = _playerPos.y + 50;
		_slash->GetTransform().pos.x = _playerPos.x;
		break;
	case Left:
		_slash->GetTransform().pos.y = _playerPos.y;
		_slash->GetTransform().pos.x = _playerPos.x - 50;
		break;
	case Right:
		_slash->GetTransform().pos.y = _playerPos.y;
		_slash->GetTransform().pos.x = _playerPos.x + 50;
		break;
	case Up:
		_slash->GetTransform().pos.y = _playerPos.y - 50;
		_slash->GetTransform().pos.x = _playerPos.x;
		break;
	case Stopped:
		break;
	default:;
	}
}

void MeleeCollider::OnTick(const double& dt)
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
					_currentScene->RemoveObject(_slash);
					_aiAgent->AiDead();
					_aiAgent = nullptr;
					break;
				}
				else
				{
					break;
				}
				break;
			}
		}

	}
	_deleteTimer += dt;
	if (_deleteTimer > _deleteTime)
	{
		_currentScene->RemoveObject(_slash);
	}
}

void MeleeCollider::OnDestroy()
{
}

void MeleeCollider::DrawPropertyUI()
{
}
