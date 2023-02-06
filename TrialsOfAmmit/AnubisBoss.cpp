#include "AnubisBoss.h"

AnubisBoss::AnubisBoss()
{
	shieldState = SHIELDED;
	currentAction = IDLE;
	_maxHealth = 500.0f;
	_currentHealth = _maxHealth;
}
