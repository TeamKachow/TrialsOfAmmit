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
	std::string roomName = "unknown";
	
	std::vector<int8_t> nav_grid_; // dynamic array 
	std::vector<int8_t> texture_grid_; // dynamic array 
	std::vector<int8_t> object_grid; // dynamic array

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
	std::vector<tileData> roomGrid = std::vector<tileData>(100);

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

	void openFromFile(const char* filePath) 
	{
		std::ifstream i(filePath);
		nlohmann::json json;
		i >> json;
		clear();

		roomX = json["roomX"];
		roomY = json["roomY"];
		
		roomGrid.clear();
		roomGrid.reserve(roomX * roomY);

		std::vector<int8_t> navGridTemp = json.at("navGrid").get<std::vector<int8_t>>();
		std::vector<int8_t> texGridTemp = json.at("texGrid").get<std::vector<int8_t>>();
		std::vector<int8_t> objGridTemp = json.at("objGrid").get<std::vector<int8_t>>();

		for (int i = 0; i < roomY; ++i)
		{
			for (int j = 0; j < roomX; ++j)
			{
				int index = i * roomX + j;
				tileData td;
				td.isSolid = navGridTemp[index];
				td.textureRef = texGridTemp[index];
				td.objectRef = objGridTemp[index];
				roomGrid.push_back(td);
			}
		}

		nlohmann::json texRef = json["texReference"];
		Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

		for (const auto& object : texRef)
		{
			textureRefData* newTexRef = new textureRefData;
			newTexRef->textureID = object["textureID"];
			newTexRef->textureRoot = object["textureRoot"];
			newTexRef->gridSizeX = object["gridSizeX"];
			newTexRef->gridSizeY = object["gridSizeY"];
			newTexRef->gridPosX = object["gridPosX"];
			newTexRef->gridPosY = object["gridPosY"];

			if (resManager->GetTexture(newTexRef->textureRoot) == nullptr) {
				resManager->LoadTexture(newTexRef->textureRoot, true, newTexRef->textureRoot);
			}

			textureRefs.push_back(newTexRef);
		}

	}

	void updateRoomSize(int currentRoomX, int currentRoomY) 
	{
		
		if (isResizing == false) {
			isResizing = true;

			// make temp copy
			int size = (currentRoomX * currentRoomY) * 2;
			roomGrid.resize(size);

			isResizing = false;
		}
	}

	void clear() {
		roomX = 10;
		roomY = 10;
		isResizing = false;

		selected = nullptr;
		roomGrid.clear();

		textureRefs.clear();
	}
};

void StartRoomMaker(bool& isActive);