#pragma once
#include <Hudson.h>
#include "BaseAbilityClass.h"
#include "Roll.h"
#include "Stun.h"
#include "Rage.h"
#include "Heal.h"
#include "RoomAOE.h"
#include "OneUP.h"

class AbilityHolder : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	BaseAbilityClass* _currentAbility;
	Roll* _roll;
	Stun* _stun;
	Rage* _rage;
	Heal* _heal;
	RoomAOE* _roomaoe;
	//OneUP* _oneup;
	

	AbilityHolder();
	~AbilityHolder();

	float _timer;
	Hudson::Input::InputManager* _input;
	
	Hudson::Audio::AudioManager* _audioMan;
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

};
