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
	std::map<int, Hudson::Render::SpriteComponent*> texture_reference_;

	std::vector<Hudson::Render::SpriteComponent*> spriteComponents;
	std::vector<Hudson::Physics::ColliderComponent*> colliderComponents;
};
