#include "Projectile.h"
#include "AiAgent.h"
#include "Chest.h"
#include "AnubisBoss.h"

Projectile::Projectile(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, WeaponTypes _weaponFiring, float _damage, float _speed, float _range) : Behaviour("ProjectileUpdatedBehaviour")
{

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
	
}
Projectile::~Projectile()
{

}
void Projectile::FromJson(const nlohmann::json& j)
{
}

void Projectile::ToJson(nlohmann::json& j)
{
}

void Projectile::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	if (_currentWeaponFiring == WT_Bow)
	{
		_projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Projectile"));
	}
	if (_currentWeaponFiring == WT_SlingShot)
	{
		_projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Rock"));
	}
	//TODO CHANGE DEPENDING ON THE WEAPON FIRING
	_projectilePhysics = new Hudson::Physics::PhysicsComponent();
	_projectileCollider = new Hudson::Physics::ColliderComponent();

	_projectileSprite->SetGridSize(glm::vec2(3, 4));
	_projectileSprite->SetGridPos(glm::vec2(0, 0));
	_projectilePhysics->SetMass(1.0f);
	_projectileSprite->SetDepthOrder(1);

	_parent->AddComponent(_projectileSprite);
	_parent->AddComponent(_projectilePhysics);
	_parent->AddComponent(_projectileCollider);
	_parent->SetName("Projectile");

	
	switch (_projectileDirection)
	{
	case Down:
		_projectilePhysics->SetVelocity(glm::vec2(0, _projectileMoveSpeed));
		_parent->GetTransform().pos.y = _spawnPos.y + 50 ;
		_parent->GetTransform().pos.x = _spawnPos.x;
		_gridY = 3;
		break;
	case Left:
		_projectilePhysics->SetVelocity(glm::vec2(-_projectileMoveSpeed, 0));
		_parent->GetTransform().pos.x = _spawnPos.x - 50;
		_parent->GetTransform().pos.y = _spawnPos.y;
		_gridY = 2;
		break;
	case Right:
		_projectilePhysics->SetVelocity(glm::vec2(_projectileMoveSpeed, 0));
		_parent->GetTransform().pos.x = _spawnPos.x + 50;
		_parent->GetTransform().pos.y = _spawnPos.y;
		_gridY = 1;
		break;
	case Up:
		_projectilePhysics->SetVelocity(glm::vec2(0, -_projectileMoveSpeed));
		_parent->GetTransform().pos.y = _spawnPos.y - 50;
		_parent->GetTransform().pos.x = _spawnPos.x;
		_gridY = 0;
		break;
	case Stopped: 
		_projectilePhysics->SetVelocity(glm::vec2(0, _projectileMoveSpeed));
		_parent->GetTransform().pos.y = _spawnPos.y + 50;
		_parent->GetTransform().pos.x = _spawnPos.x;
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
		_currentScene->RemoveObject(_parent);
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
					_currentScene->RemoveObject(_parent);
					break;
				}
			}
			else
			{
				collider->ClearColliding();
			}
			if (other->GetParent()->GetComponent<AnubisBoss>() != nullptr)
			{
				AnubisBoss* _boss = other->GetParent()->GetComponent<AnubisBoss>();
				if (_boss != nullptr)
				{
					_boss->TakeDamage(_projectileDamage);
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
					collider->ClearColliding();

					break;
				}
				else
				{
					break;
				}

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
