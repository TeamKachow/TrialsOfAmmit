#pragma once
#include "../Util/stdafx.h"
#include "../Editor/ComponentRegistry.h"

namespace Hudson::Common
{
	class Engine;
}

namespace Hudson::Editor
{
	class Editor
	{
		Common::Engine* _engine;
		ComponentRegistry* _registry;

		Entity::GameObject* _selected = nullptr;
		bool _showIds = false;
		bool _showHelp = false;

	public:
		Editor(Common::Engine* engine, ComponentRegistry* registry = nullptr);
		~Editor();

	private:

		void InfiniteButton();
		void MenuBar();
		void Scene();
		void Hierarchy();
		void ContentBrowser();
		void ComponentList();
		void Tools();
		void ObjectProperties();
		void Debug();
		void Help();

		void Draw();
	};
}