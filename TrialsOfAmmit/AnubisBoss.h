#pragma once

#include <Hudson.h>
#include "Player.h"

enum damageState 
{
	SHIELDED,
	VULNERABLE,
	ENRAGED
};

enum attackState
{
	IDLE,
	DEATHLASERS,
	PLAGUESWARM,
	HELLFIREWAVE,
	NECROMANCY
};

class AnubisBoss
{
public:
	AnubisBoss();
	~AnubisBoss();
	float _maxHealth;
	float _currentHealth;
	void TakeDamage();
	damageState shieldState;
	attackState currentAction;
	Player* player;
private:
	void SpawnLasers();
	void SpawnSwarm();
	void FireWave();
	void SpawnMummies();

	float laserCD;
	float swarmCD;
	float fireCD;
	float spawnCD;

};

