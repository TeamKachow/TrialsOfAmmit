#pragma once
#include <Hudson.h>
#include "Rooms/Room.h"
#include "Player.h"
#include <random>

using namespace std;
using namespace glm;

class Door : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	Door();
	~Door();
	void GenerateNewRoom();
	void OnCreate() override;
protected:

private:
	
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;
	void CollisionCheck();

	void DeleteRoomGameObjects();
	void MovePlayer();
	Hudson::Entity::GameObject* NewRoom;
	Hudson::Physics::ColliderComponent* DoorCollider;
	Hudson::Audio::AudioManager* _audioMan;
	Player* _player;
	string Roomname;
	int RandRoomNum;
	int _minRange;
	int _maxRange;
	bool _isActive;
	bool _isHit;
	float _ativeTimer;
	float _activeSpeed;

	vec2 newRoomPos;
	vec2 newRoomSize;
};

