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

	public:
		Editor(Common::Engine* engine, ComponentRegistry* registry = nullptr);
		~Editor();

	private:

		void InfiniteButton();
		void MenuBar();
		void Hierarchy();
		void ContentBrowser();
		void ComponentList();
		void Tools();
		void ObjectComponents();
		void Debug();

		void Draw();
	};
}