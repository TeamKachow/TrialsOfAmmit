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
		bool openInput;
		char selected;
		char keyAction[255]{};

	public:
		Editor(Common::Engine* engine);
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
		void Input();

		void Draw();
	};
}