#include "Projectile.h"
#include "AiAgent.h"

Projectile::Projectile(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, Hudson::Entity::GameObject* _projectileRef) : Behaviour("ProjectileBehaviour")
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Projectile"));
	_projectilePhysics = new Hudson::Physics::PhysicsComponent();
	_projectileCollider = new Hudson::Physics::ColliderComponent();

	
	_projectileSprite->SetGridSize(glm::vec2(3, 4));
	_projectileSprite->SetGridPos(glm::vec2(0, 0));
	_projectilePhysics->SetMass(1.0f);

	_projectile = _projectileRef;
	_projectile->AddComponent(_projectileSprite);
	_projectile->AddComponent(_projectilePhysics);
	_projectile->AddComponent(_projectileCollider);
	_projectile->SetName("Projectile");

	_projectileDirection = projectileDirection;

	_animTimer = 0;
	_animSpeed = 0.2;

	_deleteTime = 5;
	_deleteTimer = 0;

	_spawnPos = spawnPos;

	
	_currentScene = CurrentScene;
	_currentScene->AddObject(_projectile);
}

Projectile::~Projectile()
{

}

void Projectile::OnCreate()
{
	switch (_projectileDirection)
	{
	case Down:
		_projectilePhysics->SetVelocity(glm::vec2(0, 250));
		_projectile->GetTransform().pos.y = _spawnPos.y + 50 ;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 3;
		break;
	case Left:
		_projectilePhysics->SetVelocity(glm::vec2(-250, 0));
		_projectile->GetTransform().pos.x = _spawnPos.x - 50;
		_projectile->GetTransform().pos.y = _spawnPos.y;
		_gridY = 2;
		break;
	case Right:
		_projectilePhysics->SetVelocity(glm::vec2(250, 0));
		_projectile->GetTransform().pos.x = _spawnPos.x + 50;
		_projectile->GetTransform().pos.y = _spawnPos.y;
		_gridY = 1;
		break;
	case Up:
		_projectilePhysics->SetVelocity(glm::vec2(0, -250));
		_projectile->GetTransform().pos.y = _spawnPos.y - 50;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 0;
		break;
	case Stopped: 
		break;
	default: ;
	}

	//std::vector<Hudson::Physics::ColliderComponent*> colliders = _projectile->GetComponent<Hudson::Physics::ColliderComponent>();
	//std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();

	



	_projectileSprite->SetGridPos(glm::vec2(_gridX, _gridY));
}

void Projectile::OnTick(const double& dt)
{
	_animTimer += dt;
	_deleteTimer += dt;
	if(_animTimer >= _animSpeed )
	{
		_animTimer -= _animSpeed;
		_gridX++;
		_projectileSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	}
	if(_deleteTimer >= _deleteTime)
	{
		_currentScene->RemoveObject(_projectile);
	}

	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			cout << "Hit" << other << "\n";
			//cout<<other->GetParent()->GetName() << "\n";
			if (other->GetParent()->GetComponent<AiAgent>() != nullptr)
			{
				cout << other->GetParent()->GetComponent<AiAgent>()->GetParent()->GetName() << "\n";
				AiAgent* _aiAgent = other->GetParent()->GetComponent<AiAgent>();
				if(_aiAgent != nullptr)
				{
					_currentScene->RemoveObject(_projectile);
					_aiAgent->AiDead();
					_aiAgent = nullptr;
					break;
				}
				else
				{
					cout << "Agent Not Found" << other << "\n";
					break;
				}
				
				//_player = other->GetComponent<Player>();
				break;
			}


		}

	}

	
	



}

void Projectile::OnDestroy()
{
	Behaviour::OnDestroy();
}

void Projectile::DrawPropertyUI()
{
}
