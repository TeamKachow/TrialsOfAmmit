#include "PassivePickups.h"
#include <random>

using namespace std;


PassivePickups::PassivePickups(glm::vec2 _spawnpos) : Behaviour("PassivePickups")
{
	_spawnPos = _spawnpos;
	_randomPassiveInt = 0;
}

PassivePickups::~PassivePickups()
{
}

void PassivePickups::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_passiveSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Passives"));
	_passiveSprite->SetGridSize(glm::vec2(3, 1));
	_passiveSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_passiveCollider = new Hudson::Physics::ColliderComponent();

	_parent->AddComponent(_passiveSprite);
	_parent->AddComponent(_passiveCollider);
	_parent->SetName("PassivePickup");
	_parent->GetTransform().pos = _spawnPos;

	random_device rand;
	uniform_int_distribution<int> dist(0, 2);
	_randomPassiveInt = dist(rand);
	if (_randomPassiveInt == 0)
	{
		_passiveType = PT_HEAL;
		_passiveSprite->SetGridPos(glm::vec2(0, 0));
	}
	if (_randomPassiveInt == 1)
	{
		_passiveType = PT_ATTACK;
		_passiveSprite->SetGridPos(glm::vec2(1, 0));
	}
	if (_randomPassiveInt == 2)
	{
		_passiveType = PT_SPEED;
		_passiveSprite->SetGridPos(glm::vec2(2, 0));
	}
}

void PassivePickups::OnTick(const double& dt)
{
}

void PassivePickups::OnDestroy()
{
}

void PassivePickups::DrawPropertyUI()
{
}
