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

	glm::vec2 GetRoomSize() { return glm::vec2(x, y); }

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

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
	int textureID = 0;
	int gridPosX = 0;
	int gridPosY = 0;
	int gridSizeX = 1;
	int gridSizeY = 1;
	std::string textureRoot = "";

	void Clear() {
		textureID = 0;
		gridPosX = 0;
		gridPosY = 0;
		gridSizeX = 1;
		gridSizeY = 1;
		textureRoot = "";
	}
};

struct tileData{
	bool isSolid = false;
	int textureRef = 0;
	int objectRef = 0;
};

struct ImGuiRoomData
{
	int roomX = 10;
	int roomY = 10;
	bool isResizing = false;

	tileData* selected = nullptr;
	tileData* roomGrid = new tileData[roomX * roomY];

	std::vector<textureRefData*> textureRefs;

	void saveToFile(const char* filePath)
	{
		nlohmann::json roomData;
		std::ofstream writeFile(filePath);
		roomData["roomX"] = roomX;
		roomData["roomY"] = roomY;

		nlohmann::json navGridFinal;
		nlohmann::json texGridFinal;
		nlohmann::json objGridFinal;
		nlohmann::json refTextureFinal;

		for(int y = 0; y < roomY; ++y)
		{
			for (int x = 0; x < roomX; ++x)
			{
				tileData tile = roomGrid[y * roomX + x];

				if(tile.isSolid)
				{
					navGridFinal.push_back(1);
				}
				else
				{
					navGridFinal.push_back(0);
				}
				texGridFinal.push_back(tile.textureRef);
				objGridFinal.push_back(tile.objectRef);
			}
		}

		for (textureRefData* refData : textureRefs)
		{
			nlohmann::json newTexRef = {
				{"textureID", refData->textureID },
				{"textureRoot", refData->textureRoot },
				{"gridSizeX", refData->gridSizeX },
				{"gridSizeY", refData->gridSizeY },
				{"gridPosX", refData->gridPosX },
				{"gridPosY", refData->gridPosY },
			};

			refTextureFinal.push_back(newTexRef);

		}

		roomData["navGrid"] = navGridFinal;
		roomData["texGrid"] = texGridFinal;
		roomData["objGrid"] = objGridFinal;
		roomData["texReference"] = refTextureFinal;

		writeFile << std::setw(1) << roomData << std::endl;

	}

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