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
	if (shieldState == VULNERABLE)
	{
  		_currentHealth = _currentHealth - damageTaken;
		BossSprite->SetColor(vec3(1, 0, 0));
	}

	if (_currentHealth <= 0)
	{
		currentPhase = BOSS_DEAD;
	}
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
	_parent->GetTransform().pos = { 700.0f , 200.0f };

	//sets up collider
	CollisionBox = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(CollisionBox);
	_parent->SetName("Anubis");
	attacksUsed = 0;

	_aiDeathSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Blood"));
	Blood = new Hudson::Entity::GameObject;

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
	BossSprite->SetColor(vec3(1, 1, 0));
	attackCD = 5.0;
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
				_animTimer = 0.0;
				if (attacksUsed >= 5)
				{
					shieldState = VULNERABLE;
					_vulnerableTimer = 0.0;
				}
				else if (attackCD <= 0.0)
				{
					if (laserCD <= 0.0)
					{
						currentAction = DEATHLASERS;
					}
					else
					{
						if (swarmCD <= 0.0 && spawnCD <= 0.0 && fireCD <= 0.0)
						{
							random_device rand;
							uniform_int_distribution<int> dist(1, 99);
							int randChance = dist(rand);
							if (randChance < 33)
							{
								currentAction = HELLFIREWAVE;
							}
							else if (randChance > 33 && randChance < 66)
							{
								currentAction = PLAGUESWARM;
							}
							else
							{
								currentAction = NECROMANCY;
							}
						}
						else
						{
							if (fireCD <= 0.0)
							{
								currentAction = HELLFIREWAVE;
							}
							else if (spawnCD <= 0.0)
							{
								currentAction = NECROMANCY;
							}
							else if (swarmCD <= 0.0)
							{
								currentAction = PLAGUESWARM;
							}
						}
					}
				}
				break;
			case DEATHLASERS:
				Animate(dt);
				if (attackCD <= 0.0)
				{
					if (laserCD <= 0.0)
					{
						_laserAnimDone = false;
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
						break;
					}
				}
				if (_laserAnimDone)
				{
					currentAction = BOSS_IDLE;
				}
				break;
			case HELLFIREWAVE:
				if (attackCD <= 0.0)
				{
					if (fireCD <= 0.0)
					{
						Animate(dt);
						_fireTimer += dt;
						SetPlayerPos();
						if (_fireTimer >= 0.5)
						{
							if (_fireSpawned == 0)
							{
								_animStart = true;
								_fireSpawned += 1;
								Hudson::Entity::GameObject* flame1 = new Hudson::Entity::GameObject();
								flame1->AddComponent(new FireBehaviour(_playerPos));
								_currentScene->AddObject(flame1);
								_fireTimer = 0.0;
							}
							else if (_fireSpawned == 1)
							{
								_fireSpawned += 1;
								Hudson::Entity::GameObject* flame2 = new Hudson::Entity::GameObject();
								flame2->AddComponent(new FireBehaviour(_playerPos));
								_currentScene->AddObject(flame2);
								_fireTimer = 0.0;
							}
							else if (_fireSpawned == 2)
							{
								_fireSpawned += 1;
								Hudson::Entity::GameObject* flame3 = new Hudson::Entity::GameObject();
								flame3->AddComponent(new FireBehaviour(_playerPos));
								_currentScene->AddObject(flame3);
								_fireTimer = 0.0;
							}
							else
							{
								_fireSpawned = 0;
								attacksUsed += 1;
								currentAction = BOSS_IDLE;
								fireCD = 10.0;
								attackCD = 5.0;
							}
						}
					}
				}
				break;
			case PLAGUESWARM:
				if (attackCD <= 0.0)
				{
					if (swarmCD <= 0.0)
					{
						Animate(dt);
						_locustTimer += dt;
						if (_locustTimer >= 0.5)
						{
							SetCurrentPos();
							if (_locustSpawned == 0)
							{
								_locustSpawned += 1;
								Hudson::Entity::GameObject* locust1 = new Hudson::Entity::GameObject();
								locust1->AddComponent(new LocustBehaviour(glm::vec2(_currentPos.x + 10.0f, _currentPos.y)));
								_currentScene->AddObject(locust1);
								_locustTimer = 0.0;
								break;
							}
							else if (_locustSpawned == 1)
							{
								_locustSpawned += 1;
								Hudson::Entity::GameObject* locust2 = new Hudson::Entity::GameObject();
								locust2->AddComponent(new LocustBehaviour(glm::vec2(_currentPos.x - 10.0f, _currentPos.y)));
								_currentScene->AddObject(locust2);
								_locustTimer = 0.0;
								break;
							}
							else if (_locustSpawned == 2)
							{
								_locustSpawned += 1;
								Hudson::Entity::GameObject* locust3 = new Hudson::Entity::GameObject();
								locust3->AddComponent(new LocustBehaviour(glm::vec2(_currentPos.x, _currentPos.y + 10.0f)));
								_currentScene->AddObject(locust3);
								_locustTimer = 0.0;
								_locustSpawned = 0;
								swarmCD = 10.0;
								attackCD = 5.0;
								attacksUsed += 1;
								currentAction = BOSS_IDLE;
								break;
							}
							break;
						}
						break;
					}
					break;
				}
				break;
			case NECROMANCY:
				if (attackCD <= 0.0)
				{
					if (spawnCD <= 0.0)
					{
						Animate(dt);
						SetCurrentPos();
						Hudson::Entity::GameObject* mummy1 = new Hudson::Entity::GameObject();
						mummy1->AddComponent(new AiAgent(glm::vec2(_currentPos.x, _currentPos.y + 100.0f)));
						_currentScene->AddObject(mummy1);
						attackCD = 5.0;
						spawnCD = 30.0;
						attacksUsed += 1;
						currentAction = BOSS_IDLE;
					}
				}
				break;
			}
			break;
		case VULNERABLE:
			BossSprite->SetColor(vec3(1, 1, 1));
			_vulnerableTimer += dt;
			if (_vulnerableTimer >= 10.0)
			{
				shieldState = SHIELDED;
				BossSprite->SetColor(vec3(1, 1, 0));
				attacksUsed = 0;
			}
			break;
		}
		break;
	case BOSS_DEAD:
		AiDead();
		break;
	}
}

void AnubisBoss::SetCurrentPos()
{
	_currentPos = _parent->GetTransform().pos;
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

void AnubisBoss::AiDead()
{
	//TODO: Remove the AI from the scene after the animaion 
	_currentScene->RemoveObject(Blood);
	_currentScene->RemoveObject(_parent);
}

void AnubisBoss::Animate(float dt)
{
	_animTimer += dt;
	switch (currentAction)
	{
	case BOSS_IDLE:
		BossSprite->SetGridPos(glm::vec2(0, 0));
		break;
	case HELLFIREWAVE:
		if (_animTimer >= 0.6)
		{
			BossSprite->SetGridPos(glm::vec2(0, 0));
		}
		else if (_animTimer >= 0.5)
		{
			BossSprite->SetGridPos(glm::vec2(4, 1));
		}
		else if (_animTimer >= 0.4)
		{
			BossSprite->SetGridPos(glm::vec2(3, 1));
		}
		else if (_animTimer >= 0.3)
		{
			BossSprite->SetGridPos(glm::vec2(2, 1));
		}
		else if (_animTimer >= 0.2)
		{
			BossSprite->SetGridPos(glm::vec2(1, 1));
		}
		else
		{
			BossSprite->SetGridPos(glm::vec2(0, 1));
		}
		break;
	case PLAGUESWARM:
		if (_animTimer >= 0.6)
		{
			BossSprite->SetGridPos(glm::vec2(0, 0));
		}
		else if (_animTimer >= 0.5)
		{
			BossSprite->SetGridPos(glm::vec2(4, 2));
		}
		else if (_animTimer >= 0.4)
		{
			BossSprite->SetGridPos(glm::vec2(3, 2));
		}
		else if (_animTimer >= 0.3)
		{
			BossSprite->SetGridPos(glm::vec2(2, 2));
		}
		else if (_animTimer >= 0.2)
		{
			BossSprite->SetGridPos(glm::vec2(1, 2));
		}
		else
		{
			BossSprite->SetGridPos(glm::vec2(0, 2));
		}
		break;
	case DEATHLASERS:
		if (_animTimer >= 0.8)
		{
			BossSprite->SetGridPos(glm::vec2(0, 0));
			_laserAnimDone = true;
		}
		else if (_animTimer >= 0.7)
		{
			BossSprite->SetGridPos(glm::vec2(6, 4));
		}
		else if (_animTimer >= 0.6)
		{
			BossSprite->SetGridPos(glm::vec2(5, 4));
		}
		else if (_animTimer >= 0.5)
		{
			BossSprite->SetGridPos(glm::vec2(4, 4));
		}
		else if (_animTimer >= 0.4)
		{
			BossSprite->SetGridPos(glm::vec2(3, 4));
		}
		else if (_animTimer >= 0.3)
		{
			BossSprite->SetGridPos(glm::vec2(2, 4));
		}
		else if (_animTimer >= 0.2)
		{
			BossSprite->SetGridPos(glm::vec2(1, 4));
		}
		else if (_animTimer >= 0.1)
		{
			BossSprite->SetGridPos(glm::vec2(0, 4));
		}
		break;
	case NECROMANCY:
		if (_animTimer >= 0.6)
		{
			BossSprite->SetGridPos(glm::vec2(0, 0));
		}
		else if (_animTimer >= 0.5)
		{
			BossSprite->SetGridPos(glm::vec2(4, 3));
		}
		else if (_animTimer >= 0.4)
		{
			BossSprite->SetGridPos(glm::vec2(3, 3));
		}
		else if (_animTimer >= 0.3)
		{
			BossSprite->SetGridPos(glm::vec2(2, 3));
		}
		else if (_animTimer >= 0.2)
		{
			BossSprite->SetGridPos(glm::vec2(1, 3));
		}
		else
		{
			BossSprite->SetGridPos(glm::vec2(0, 3));
		}
		break;
	}
}