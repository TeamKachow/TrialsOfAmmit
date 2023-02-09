#include "LaserBehaviour.h"

LaserBehaviour::LaserBehaviour(glm::vec2 spawnPos, int laserType) : Behaviour("LaserBehaviour")
{
	_laserType = laserType;
	_spawnPos = spawnPos;
}

LaserBehaviour::~LaserBehaviour()
{
}

void LaserBehaviour::Charge()
{
	_chargeTimer = 0.0;
	_fireTimer = 0.0;
	_deactivateTimer = 0.0;
	_currentState = CHARGING;
}

void LaserBehaviour::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	if (_laserType == 0)
	{
		LaserSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("LaserVert"));
		LaserSprite->SetGridSize(glm::vec2(5, 3));
		LaserSprite->SetGridPos(glm::vec2(0, 1));
		_parent->GetTransform().scale.x = 96.0f;
		_parent->GetTransform().scale.y = 960.0f;
	}
	else
	{
		LaserSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("LaserHori"));
		LaserSprite->SetGridSize(glm::vec2(5, 3));
		LaserSprite->SetGridPos(glm::vec2(0, 1));
		_parent->GetTransform().scale.x = 960.0f;
		_parent->GetTransform().scale.y = 96.0f;
	}
	CollisionBox = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(CollisionBox);
	_parent->SetName("Laser");
	LaserSprite->SetDepthOrder(20);
	_parent->AddComponent(LaserSprite);
	_parent->GetTransform().pos = _spawnPos;
	Charge();
}

void LaserBehaviour::OnDestroy()
{
}

void LaserBehaviour::OnTick(const double& dt)
{
	if (_currentState != IDLE)
	{
		Animate(dt);

		if (_currentState == CHARGING)
		{
			_chargeTimer += dt;

			if (_chargeTimer >= 1.5)
			{
				_currentState = FIRING;
			}
		}
		else if (_currentState == FIRING)
		{
			if (_laserCooldown < 1.0)
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
							_player = other->GetParent()->GetComponent<Player>();
							if (_player != nullptr)
							{
								_player->TakeDamage(1.0f);
								_laserCooldown = 1.0;

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
			}
			_laserCooldown -= dt;
			_fireTimer += dt;
			_animTimer += dt;
			if (_fireTimer >= 2.0)
			{
				_currentState = DEACTIVATING;
			}
		}
		else
		{
			_deactivateTimer += dt;
			if (_deactivateTimer >= 1.0)
			{
				_currentState = IDLE;
			}
		}
	}
	else
	{
		LaserSprite->SetGridPos(glm::vec2(0, 0));
	}
}

void LaserBehaviour::Animate(float deltaTime)
{
	if (_currentState == CHARGING)
	{
		if (_chargeTimer > 1.5)
		{
			LaserSprite->SetGridPos(glm::vec2(4, 1));
		}
		else if (_chargeTimer > 1.4)
		{
			LaserSprite->SetGridPos(glm::vec2(3, 1));
		}
		else if (_chargeTimer > 0.9)
		{
			LaserSprite->SetGridPos(glm::vec2(2, 1));
		}
		else if (_chargeTimer > 0.6)
		{
			LaserSprite->SetGridPos(glm::vec2(1, 1));
		}
		else if (_chargeTimer > 0.3)
		{
			LaserSprite->SetGridPos(glm::vec2(0, 1));
		}
		else
		{
			LaserSprite->SetGridPos(glm::vec2(0, 0));
		}
	}
	else if (_currentState == FIRING)
	{
		if (_animTimer > 0.5)
		{
			LaserSprite->SetGridPos(glm::vec2(4, 2));
			_animTimer = 0.0;
		}
		else if (_animTimer > 0.4)
		{
			LaserSprite->SetGridPos(glm::vec2(3, 2));
		}
		else if (_animTimer > 0.3)
		{
			LaserSprite->SetGridPos(glm::vec2(2, 2));
		}
		else if (_animTimer > 0.2)
		{
			LaserSprite->SetGridPos(glm::vec2(1, 2));
		}
		else if (_animTimer > 0.1)
		{
			LaserSprite->SetGridPos(glm::vec2(0, 2));
		}
	}
	else if (_currentState == DEACTIVATING)
	{
		if (_deactivateTimer > 0.9)
		{
			LaserSprite->SetGridPos(glm::vec2(0, 1));
		}
		else if (_deactivateTimer > 0.6)
		{
			LaserSprite->SetGridPos(glm::vec2(0, 1));
		}
		else if (_deactivateTimer > 0.3)
		{
			LaserSprite->SetGridPos(glm::vec2(1, 1));
		}
		else if (_deactivateTimer > 0.0)
		{
			LaserSprite->SetGridPos(glm::vec2(2, 1));
		}
	}
}
void LaserBehaviour::FromJson(const nlohmann::json& j)
{
}

void LaserBehaviour::ToJson(nlohmann::json& j)
{
}

