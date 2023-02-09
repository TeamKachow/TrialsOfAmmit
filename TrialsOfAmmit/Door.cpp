#include "Door.h"
#include "AiAgent.h"
#include "Chest.h"
#include "Rooms/Room.h"
#include "PickupWeapon.h"
#include "PickupAbilitys.h"
#include "PassivePickups.h"
Door::Door() : Behaviour("DoorBehaviour")
{

}

Door::~Door()
{

}

void Door::OnCreate()
{
	DoorCollider = new Hudson::Physics::ColliderComponent;
	_parent->AddComponent(DoorCollider);
	_isActive = false;
	_activeSpeed = 1;
	_isHit = false;

	_minRange = 0;
	_maxRange = 5;

	auto _sceneObjects = _parent->GetScene()->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			break;
		}
	}
	
}

void Door::OnDestroy()
{

}

void Door::OnTick(const double& dt)
{
	CollisionCheck();
	_ativeTimer += dt;
	if (_ativeTimer > _activeSpeed)
	{
		_isActive = true;
	}
	if (_isHit)
	{
		GenerateNewRoom();
	}
}

void Door::DrawPropertyUI()
{

}

void Door::FromJson(const nlohmann::json& j)
{

}

void Door::ToJson(nlohmann::json& j)
{

}

void Door::CollisionCheck()
{
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other->GetParent()->GetComponent<Player>() != nullptr)
			{
				Player* _playerCollision = other->GetParent()->GetComponent<Player>();
				if (_playerCollision != nullptr)
				{
					_isHit = true;
					collider->ClearColliding();

					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void Door::GenerateNewRoom()
{
	
	random_device rand;
	uniform_int_distribution<int> dist(_minRange, _maxRange);
	RandRoomNum = dist(rand);

	std::cout << "Random Room Num: " << RandRoomNum << std::endl;

	Roomname = "Rooms/room" + to_string(RandRoomNum) + ".room";
	Room* RoomComp = new class Room(Roomname.c_str());

	newRoomSize = RoomComp->GetRoomSize();

	NewRoom = new Hudson::Entity::GameObject;
	NewRoom->AddComponent(RoomComp);
	MovePlayer();
	_parent->GetScene()->AddObject(NewRoom);
	DeleteRoomGameObjects();

}

void Door::DeleteRoomGameObjects()
{

	auto _sceneObjects = _parent->GetScene()->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetComponent<Room>() != nullptr) {
			// This will not work in debug - memory leak present when removing objects
			#ifdef DEBUG
				other->GetTransform().pos = glm::vec2(10000, 10000);
			#else 
				other->GetScene()->RemoveObject(other);
			#endif // DEBUG
		}
		else if (other->GetComponent<AiAgent>() != nullptr) {
			other->GetScene()->RemoveObject(other);
		}
		else if (other->GetComponent<Chest>() != nullptr) {
			other->GetScene()->RemoveObject(other);
		}
		else if (other->GetComponent<PickupWeapon>() != nullptr) {
			other->GetScene()->RemoveObject(other);
		}
		else if (other->GetComponent<PickupAbilitys>() != nullptr) {
			other->GetScene()->RemoveObject(other);
		}
		else if (other->GetComponent<PassivePickups>() != nullptr) {
			other->GetScene()->RemoveObject(other);
		}
	}
	_isHit = false;
	_parent->GetScene()->RemoveObject(_parent);
}

void Door::MovePlayer()
{	
	int maxRoomX = 25;
	int maxRoomY = 14;
	
	vec2 roomTransform((maxRoomX - newRoomSize.x) * 32, (maxRoomY - newRoomSize.y) * 32); // 64 is the room transform size, could do more work to grab room transform

	_player->SetPosition(roomTransform + vec2(newRoomSize.x * 64 / 2, newRoomSize.y * 64 - 128));
	//_player->SetPosition(NewRoom->GetTransform().pos);
}
