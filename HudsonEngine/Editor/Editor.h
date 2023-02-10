#pragma once
#include "../Util/stdafx.h"
#include "../Common/ComponentRegistry.h"

struct Action
{
	std::string actionName;
	bool isSelected;
};

struct ToolData
{
	std::function<void(bool&)> function;
	bool isRepeatingFunction = false;
	bool isActive = false;
};

namespace Hudson::Common
{
	class Engine;
}

namespace Hudson::World
{
	class Scene;
}

namespace Hudson::Editor
{
	class Editor
	{
	private:
		struct SceneMeta
		{
			bool pendingChanges = true;
			std::string filePath;
			std::string backup;
		};

		Common::Engine* _engine;

		bool openInput;
		char selected;
		char keyAction[255]{};

		Entity::GameObject* _selectedObj = nullptr;
		bool _showIds = false;
		bool _showHelp = false;
		bool _showImguiDemo = false;

		std::map<World::Scene*, SceneMeta> _sceneMeta;
		World::Scene* _sceneToSave;
		std::string _sceneToLoad;

	public:
		Editor(Common::Engine* engine);
		~Editor();

		void AddTool(std::string, ToolData);

		ImVec2 viewportSize = { 0,0 };
		ImVec2 cursorPos = { 0,0 };
		ImVec2 worldSpacePos = { 0,0 };

	private:
        SceneMeta& GetSceneMeta(World::Scene* scene);
        void ShowSceneSaveAs(World::Scene* scene);

		static bool LoadImGuiImage(const char* filename, unsigned int* out_texture, int* out_width, int* out_height);
		void InfiniteButton();
		void MenuBar();
		void Viewport();
		void Hierarchy();
		void ContentBrowser();
		void ComponentList();
		void Tools();
		void ObjectProperties();
		void DebugLog();
		void Help();
		void Input();
		void SaveDialogs();

		void Draw();

	private:
		int my_image_width = 0;
		int my_image_height = 0;

		GLuint directoryIcon = 0;
		GLuint fileIcon = 0;

		std::filesystem::path currentPath;

		std::map<std::string, ToolData> toolFunctions;
	};

}

