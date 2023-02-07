#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include "Behaviour.h"
#include "GameObject.h"
#include "../Common/ResourceManager.h"
#include "../Common/IEditable.h"
#include "../Render/SpriteComponent.h"
#include "../Physics/ColliderComponent.h"
#include "../Util/stdafx.h"

class Room : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	Room();
	Room(const char* roomFile);
	~Room() override;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;

	void DrawPropertyUI() override;

private:
	int x, y;
	
	char* nav_grid_; // dynamic array 
	char* texture_grid_; // dynamic array 
	char* object_grid; // dynamic array

	std::map<int, Hudson::Render::SpriteComponent*> texture_reference_;
	std::map<int, Hudson::Entity::GameObject*> obj_reference_;

	std::vector<Hudson::Render::SpriteComponent*> spriteComponents;
	std::vector<Hudson::Physics::ColliderComponent*> colliderComponents;
};

struct textureRefData {
	int textureID = -1;
	int gridPosX = 0;
	int gridPosY = 0;
	int gridSizeX = 1;
	int gridSizeY = 1;
	std::string textureRoot = "";

	void Clear() {
		textureID = -1;
		gridPosX = 0;
		gridPosY = 0;
		gridSizeX = 1;
		gridSizeY = 1;
		textureRoot = "";
	}
};

struct tileData{
	bool isSolid = false;
	int textureRef = -1;
	int objectRef = -1;
};

struct ImGuiRoomData
{
	int roomX = 10;
	int roomY = 10;
	bool isResizing = false;

	tileData* selected = nullptr;
	tileData* roomGrid = new tileData[roomX * roomY];

	std::vector<textureRefData*> textureRefs;



	void updateRoomSize(int currentRoomX, int currentRoomY) {
		
		if (isResizing == false) {
			isResizing = true;

			// make temp copy
			int size = (currentRoomX * currentRoomY) * 2;
			tileData* tempGridData = new tileData[size];
			for (int i = 0; i < size; ++i) {
				tempGridData[i] = roomGrid[i];
			}
			roomGrid = tempGridData;

			isResizing = false;
		}
	}
};

void StartRoomMaker(bool& isActive);