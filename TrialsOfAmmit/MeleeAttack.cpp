#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene, Hudson::Entity::GameObject* _slashRef) : Behaviour("MeleeBehaviour")
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_slashSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Slash"));

	_slashSprite->SetGridSize(glm::vec2(3, 4));
	_slashSprite->SetGridPos(glm::vec2(0, 0));
	_slashSprite->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));

	_slash = _slashRef;

	_slash->AddComponent(_slashSprite);
	
	_slash->SetName("SlashAttack");

	_slashDirection = slashDirection;

	_animTimer = 0;
	_animSpeed = 0.2;

	_gridX = 0;
	_gridY = 0;

	_deleteTime = 0.5;
	_deleteTimer = 0;

	_playerPos = playerPos;

	_currentScene = currentScene;
	_currentScene->AddObject(_slash);
}

MeleeAttack::~MeleeAttack()
{
}

void MeleeAttack::OnCreate()
{
	switch (_slashDirection) {
		case Down:
			_slash->GetTransform().pos.y = _playerPos.y + 50;
			_slash->GetTransform().pos.x = _playerPos.x;
			_gridY = 3;
			break;
		case Left:
			_slash->GetTransform().pos.y = _playerPos.y;
			_slash->GetTransform().pos.x = _playerPos.x - 50;
			_gridY = 2;
			break;
		case Right:
			_slash->GetTransform().pos.y = _playerPos.y;
			_slash->GetTransform().pos.x = _playerPos.x + 50;
			_gridY = 1;
			break;
		case Up:
			_slash->GetTransform().pos.y = _playerPos.y - 50;
			_slash->GetTransform().pos.x = _playerPos.x;
			_gridY = 0;
			break;
		case Stopped: 
			_slash->GetTransform().pos.y = _playerPos.y + 50;
			_slash->GetTransform().pos.x = _playerPos.x;
			break;
		default: ;
	}
	_slashSprite->SetGridPos(glm::vec2(0, 0));


}

void MeleeAttack::OnTick(const double& dt)
{
	_animTimer += dt;
	_deleteTimer += dt;
	if (_animTimer >= _animSpeed)
	{
		_animTimer -= _animSpeed;
		_gridX++;
		_slashSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	}
	if (_deleteTimer >= _deleteTime)
	{
		_currentScene->RemoveObject(_slash);
	}
}

void MeleeAttack::OnDestroy()
{

}

void MeleeAttack::DrawPropertyUI()
{


}
