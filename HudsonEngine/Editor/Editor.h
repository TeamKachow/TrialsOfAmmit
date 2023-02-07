#pragma once
#include "../Util/stdafx.h"
#include "../Editor/ComponentRegistry.h"
#include "../Render/Texture.h"

struct Action
{
	std::string actionName;
	bool isSelected;
};

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

		Entity::GameObject* _selected = nullptr;
		bool _showIds = false;
		bool _showHelp = false;

	public:
		Editor(Common::Engine* engine, ComponentRegistry* registry = nullptr);
		~Editor();

		ImVec2 viewportSize = { 0,0 };
		ImVec2 cursorPos = { 0,0 };
		ImVec2 worldSpacePos = { 0,0 };

	private:

		static bool LoadImGuiImage(const char* filename, unsigned int* out_texture, int* out_width, int* out_height);
		void InfiniteButton();
		void MenuBar();
		void Viewport();
		void Hierarchy();
		void ContentBrowser();
		void ComponentList();
		void Tools();
		void ObjectProperties();
		void Debug();
		void Help();
		void Input();

		void Draw();

	private:
		// const std::filesystem::path  filePath = "../DemoGame";

		int my_image_width = 0;
		int my_image_height = 0;
		GLuint directoryIcon = 0;
		GLuint fileIcon = 0;

		std::filesystem::path currentPath;
	};
}