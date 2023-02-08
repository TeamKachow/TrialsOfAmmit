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
protected:

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;
	void CollisionCheck();
	void GenerateNewRoom();
	void MovePlayer();
	Hudson::Entity::GameObject* CurrentRoom;
	Player* _player;
	string Roomname;
	int RandRoomNum;
	int _minRange;
	int _maxRange;

};

