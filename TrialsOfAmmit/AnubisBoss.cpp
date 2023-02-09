#include "AnubisBoss.h"

AnubisBoss::AnubisBoss(glm::vec2 spawnPos) : Behaviour("AnubisBehaviour")
{
	shieldState = SHIELDED;
	currentAction = BOSS_IDLE;
	currentPhase = PHASE1;
	_maxHealth = 500.0f;
	_currentHealth = _maxHealth;
}

AnubisBoss::~AnubisBoss()
{
}

void AnubisBoss::TakeDamage(float damageTaken)
{
	//removes damage passed to it and calls dead once health is 0
	if (shieldState == VULNERABLE)
	{
		_currentHealth = _currentHealth - damageTaken;
		BossSprite->SetColor(vec3(1, 0, 0));
	}

	if (_currentHealth <= 0)
	{
		currentPhase = BOSS_DEAD;
	}
	isDamaged = true;
}

void AnubisBoss::FromJson(const nlohmann::json& j)
{
}

void AnubisBoss::ToJson(nlohmann::json& j)
{
}

void AnubisBoss::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	BossSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Anubis"));
	BossSprite->SetGridSize(glm::vec2(7, 5));
	BossSprite->SetGridPos(glm::vec2(0, 0));
	BossSprite->SetDepthOrder(8);
	_parent->AddComponent(BossSprite);
	_parent->GetTransform().scale.y = 128.0f;
	_parent->GetTransform().scale.x = 96.0f;

	//sets up collider
	CollisionBox = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(CollisionBox);
	_parent->SetName("Anubis");
	attacksUsed = 0;

	_currentScene = _parent->GetScene();

	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			break;
		}
	}
}

void AnubisBoss::OnDestroy()
{
}

void AnubisBoss::OnTick(const double& dt)
{
	if (laserCD > 0.0)
	{
		laserCD -= dt;
	}
	if (swarmCD > 0.0)
	{
		swarmCD -= dt;
	}
	if (fireCD > 0.0)
	{
		fireCD -= dt;
	}
	if (spawnCD > 0.0)
	{
		spawnCD -= dt;
	}
	if (attackCD > 0.0)
	{
		attackCD -= dt;
	}
	switch (currentPhase)
	{
	case PHASE1:
		switch (shieldState)
		{
		case SHIELDED:
			switch (currentAction)
			{
			case BOSS_IDLE:
				currentAction = DEATHLASERS;
				break;
			case DEATHLASERS:
				if (attackCD <= 0.0)
				{
					if (laserCD <= 0.0)
					{
						auto _sceneObjects = _currentScene->GetObjects();
						for (Hudson::Entity::GameObject* other : _sceneObjects)
						{
							if (other->GetName() == "Laser")
							{
								other->GetComponent<LaserBehaviour>()->Charge();
							}
						}
						laserCD = 20.0;
						attackCD = 5.0;
						attacksUsed += 1;
						currentAction = BOSS_IDLE;
					}
				}
				break;
			}
			break;
		case VULNERABLE:
			break;
		}
		break;
	case PHASE2:
		switch (shieldState)
		{
		case SHIELDED:
		{
			break;
		}
		case VULNERABLE:
			break;
		}
		break;
	case BOSS_DEAD:
		break;
	}
}

void AnubisBoss::SpawnLasers()
{
}

void AnubisBoss::SpawnSwarm()
{
}

void AnubisBoss::FireWave()
{
}

void AnubisBoss::SpawnMummies()
{
}

void AnubisBoss::SetPlayerPos()
{
	if (_player == nullptr)
	{
		auto _sceneObjects = _currentScene->GetObjects();

		for (Hudson::Entity::GameObject* other : _sceneObjects)
		{

			if (other->GetName() == "Player")
			{
				_player = other->GetComponent<Player>();
				break;
			}
		}
	}
	if (_player != nullptr)
	{
		_playerPos = _player->GetParent()->GetTransform().pos;
	}
}
