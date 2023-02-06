#pragma once

#include <Hudson.h>
#include "Player.h"

enum damageState 
{
	SHIELDED,
	VULNERABLE
};

enum attackState
{
	IDLE,
	DEATHLASERS,
	PLAGUESWARM,
	WITHERINGWAVE,
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
};

