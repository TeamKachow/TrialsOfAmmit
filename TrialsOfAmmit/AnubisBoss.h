#pragma once

#include <Hudson.h>
#include "Player.h"
#include "LaserBehaviour.h"
#include "LocustBehaviour.h"
#include "FireBehaviour.h"
#include "AiAgent.h"

enum phase
{
	PHASE1,
	PHASE2,
	BOSS_DEAD
};

enum damageState
{
	SHIELDED,
	VULNERABLE,
};

enum attackState
{
	BOSS_IDLE,
	DEATHLASERS,
	PLAGUESWARM,
	HELLFIREWAVE,
	NECROMANCY
};

class AnubisBoss : public Hudson::Entity::Behaviour
{
public:
	AnubisBoss(glm::vec2 spawnPos = { 100,100 });
	~AnubisBoss();
	float _maxHealth;
	float _currentHealth;

	void TakeDamage(float damageTaken);

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	Hudson::Render::SpriteComponent* BossSprite;
	Hudson::Physics::ColliderComponent* CollisionBox;
private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;

	void SpawnLasers();
	void SpawnSwarm();
	void FireWave();
	void SpawnMummies();

protected:
	Hudson::World::Scene* _currentScene;
	double attackCD;
	double laserCD;
	double swarmCD;
	double fireCD;
	double spawnCD;
	bool isDamaged;
	int attacksUsed;
	Player* _player;
	damageState shieldState;
	attackState currentAction;
	phase currentPhase;
	glm::vec2 _spawnPos;
	glm::vec2 _playerPos;
	void SetPlayerPos();
};

