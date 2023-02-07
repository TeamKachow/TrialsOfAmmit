#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene) : Behaviour("MeleeBehaviour")
{
	_animTimer = 0;
	_animSpeed = 0.1;

	_gridX = 0;
	_gridY = 0;

	_deleteTime = 0.3;
	_deleteTimer = 0;

	_playerPos = playerPos;
	_slashDirection = slashDirection;
	_currentScene = currentScene;

}

MeleeAttack::~MeleeAttack()
{
}

void MeleeAttack::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_slashSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Slash"));

	_slashSprite->SetGridSize(glm::vec2(3, 4));
	_slashSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_parent->AddComponent(_slashSprite);
	_parent->SetName("SlashAttack");
	_slashSprite->SetDepthOrder(-1);

	switch (_slashDirection) {
		case Down:
			_parent->GetTransform().pos.y = _playerPos.y + 50;
			_parent->GetTransform().pos.x = _playerPos.x;
			_gridY = 3;
			break;
		case Left:
			_parent->GetTransform().pos.y = _playerPos.y;
			_parent->GetTransform().pos.x = _playerPos.x - 50;
			_gridY = 2;
			break;
		case Right:
			_parent->GetTransform().pos.y = _playerPos.y;
			_parent->GetTransform().pos.x = _playerPos.x + 50;
			_gridY = 1;
			break;
		case Up:
			_parent->GetTransform().pos.y = _playerPos.y - 50;
			_parent->GetTransform().pos.x = _playerPos.x;
			_gridY = 0;
			break;
		case Stopped: 
			_parent->GetTransform().pos.y = _playerPos.y + 50;
			_parent->GetTransform().pos.x = _playerPos.x;
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
		_currentScene->RemoveObject(_parent);
	}
}

void MeleeAttack::OnDestroy()
{

}

void MeleeAttack::DrawPropertyUI()
{


}
