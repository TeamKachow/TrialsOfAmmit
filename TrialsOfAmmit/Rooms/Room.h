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

// ImGui Room Maker
inline void StartRoomMaker(bool& isActive)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::SetNextWindowPos(ImVec2(0,0));
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Room Maker", nullptr, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open");
			ImGui::MenuItem("Save");
			if(ImGui::MenuItem("Exit"))
			{
				isActive = false;
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
}
