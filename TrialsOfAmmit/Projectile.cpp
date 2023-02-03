#include "Projectile.h"
#include "AiAgent.h"


Projectile::~Projectile()
{

}

Projectile::Projectile(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, Hudson::Entity::GameObject* _projectileRef, WeaponTypes _weaponFiring, float _damage, float _speed, float _range) : Behaviour("ProjectileUpdatedBehaviour")
{
	std::cout << "Firing Through new Build Class" << "\n";
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	if (_weaponFiring == WT_Bow)
	{
		_projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Projectile"));
	}
	if (_weaponFiring == WT_SlingShot)
	{
		_projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Rock"));
	}
	//TODO CHANGE DEPENDING ON THE WEAPON FIRING
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

	_currentWeaponFiring = _weaponFiring; //Change Behavoir Depending on which on 

	_projectileDamage = _damage;
	_projectileMoveSpeed = _speed;
	_projectileRange = _range;

	_animTimer = 0;
	_animSpeed = 0.2;

	_deleteTime = 5;
	_deleteTimer = 0;

	_spawnPos = spawnPos;

	_currentScene = CurrentScene;
	_currentScene->AddObject(_projectile);
}

void Projectile::OnCreate()
{
	switch (_projectileDirection)
	{
	case Down:
		_projectilePhysics->SetVelocity(glm::vec2(0, _projectileMoveSpeed));
		_projectile->GetTransform().pos.y = _spawnPos.y + 50 ;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 3;
		break;
	case Left:
		_projectilePhysics->SetVelocity(glm::vec2(-_projectileMoveSpeed, 0));
		_projectile->GetTransform().pos.x = _spawnPos.x - 50;
		_projectile->GetTransform().pos.y = _spawnPos.y;
		_gridY = 2;
		break;
	case Right:
		_projectilePhysics->SetVelocity(glm::vec2(_projectileMoveSpeed, 0));
		_projectile->GetTransform().pos.x = _spawnPos.x + 50;
		_projectile->GetTransform().pos.y = _spawnPos.y;
		_gridY = 1;
		break;
	case Up:
		_projectilePhysics->SetVelocity(glm::vec2(0, -_projectileMoveSpeed));
		_projectile->GetTransform().pos.y = _spawnPos.y - 50;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 0;
		break;
	case Stopped: 
		_projectilePhysics->SetVelocity(glm::vec2(0, _projectileMoveSpeed));
		_projectile->GetTransform().pos.y = _spawnPos.y + 50;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 3;
		break;
	default: ;
	}

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
	if(_deleteTimer >= _projectileRange)
	{
		_currentScene->RemoveObject(_projectile);
	}

	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>(); //TODO Make it so it can only Collide Once
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other->GetParent()->GetComponent<AiAgent>() != nullptr)
			{
				AiAgent* _aiAgent = other->GetParent()->GetComponent<AiAgent>();
				if(_aiAgent != nullptr)
				{
					_aiAgent->TakeDamage(_projectileDamage);
					collider->ClearColliding();
					_currentScene->RemoveObject(_projectile);
					break;
				}
			}
			else
			{
				collider->ClearColliding();
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
