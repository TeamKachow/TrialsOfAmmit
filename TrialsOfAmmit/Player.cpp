#include "Player.h"



Player::Player(Hudson::Render::SpriteComponent* playerSprite, double animSpeed) : Behaviour("PlayerTest")
{
	_playerSprite = playerSprite;
	_playerAnimSpeed = animSpeed;
	_playerDirection = Down;
	_playerFireRate = 0.8;
	_testTimer = 0;
	_gridX = _playerSprite->GetGridPos().x;
	_gridY = _playerSprite->GetGridPos().y;
}

Player::~Player()
{
	
}

void Player::TakeDamage(float _damageTaken)
{
	_playerHealth = _playerHealth - _damageTaken;
}

void Player::OnCreate()
{
	
}

void Player::OnTick(const double& dt)
{
	switch(_playerDirection)
	{
	case Down:
		MoveDown();
		break;
	case Left:
		MoveLeft();
		break;
	case Right:
		MoveRight();
		break;
	case Up:
		MoveUp();
		break;
	case Stopped:
		StopMove();
		break;
	default: ;
	}

	_playerAnimTimer += dt;

	_playerSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	

}

void Player::Fire()
{
	/*Hudson::Common::Engine* engine;
	auto AllScenes = Hudson::Common::Engine*::GetSceneManager();
	auto CurrentScene = AllScenes.find(0);*/

	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	Hudson::Render::SpriteComponent* _projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Projectile"));;
	Hudson::Physics::PhysicsComponent* _projectilePhysics = new Hudson::Physics::PhysicsComponent();;
	Hudson::Physics::ColliderComponent* _projectileCollider = new Hudson::Physics::ColliderComponent();

	_projectileSprite->SetSize(glm::vec2(32.0f, 32.0f));
	_projectileSprite->SetGridSize(glm::vec2(3, 0));
	_projectileSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_projectilePhysics->SetMass(1.0f);
	_projectilePhysics->SetForce(glm::vec2(0.0, 0));
	_projectilePhysics->SetAcceleration(glm::vec2(0, 0), true);
	_projectilePhysics->SetVelocity(glm::vec2(0, 0));


	Hudson::Entity::GameObject* _projectile = new Hudson::Entity::GameObject();
	_projectile->AddComponent(_projectileSprite);
	//_projectile->AddComponent(new Player(playerSprite));
	_projectile->AddComponent(_projectilePhysics);
	_projectile->AddComponent(_projectileCollider);
	/*CurrentScene->AddObject(_projectile);*/
	
}

void Player::MoveUp()
{
	_gridY = 3;
	AnimMove();
	std::vector<Hudson::Physics::PhysicsComponent*> _playerPhysics = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();

	if (!_playerPhysics.empty())
	{
		_playerPhysic = _playerPhysics.front();

	}
	_playerPhysic->SetVelocity(glm::vec2(0, -20));
}

void Player::MoveDown()
{
	_gridY = 0;
	AnimMove();
	Fire();
	std::vector<Hudson::Physics::PhysicsComponent*> _playerPhysics = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();

	if (!_playerPhysics.empty())
	{
		_playerPhysic = _playerPhysics.front();

	}
	_playerPhysic->SetVelocity(glm::vec2(0, 20));
}

void Player::MoveRight()
{
	_gridY = 2;
	AnimMove();
	std::vector<Hudson::Physics::PhysicsComponent*> _playerPhysics = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();

	if (!_playerPhysics.empty())
	{
		_playerPhysic = _playerPhysics.front();

	}
	_playerPhysic->SetVelocity(glm::vec2(20, 0));
}

void Player::MoveLeft()
{
	_gridY = 1;
	AnimMove();
	std::vector<Hudson::Physics::PhysicsComponent*> _playerPhysics = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();

	if (!_playerPhysics.empty())
	{
		_playerPhysic = _playerPhysics.front();

	}
	_playerPhysic->SetVelocity(glm::vec2(-20, 0));
}

void Player::StopMove()
{
}

void Player::AnimMove()
{
	if (_playerAnimTimer >= _playerAnimSpeed)
	{
		_playerAnimTimer -= _playerAnimSpeed;

		glm::vec2 spriteGridSize = _playerSprite->GetGridSize();

		_gridX++;

		if (_gridX > spriteGridSize.x - 1)
		{
			_gridX = 0;
		}

	}
}


void Player::OnDestroy()
{
}

void Player::DrawPropertyUI()
{
}
