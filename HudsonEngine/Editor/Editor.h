#pragma once
#include "../Util/stdafx.h"
#include "../Editor/ComponentRegistry.h"

struct Action
{
	std::string actionName;
	bool isSelected;
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
			bool pendingChanges = false;
			std::string filePath;
			std::string backup;
		};

		Common::Engine* _engine;
		ComponentRegistry* _registry;
		bool openInput;
		char selected;
		char keyAction[255]{};

		Entity::GameObject* _selectedObj = nullptr;
		bool _showIds = false;
		bool _showHelp = false;

		std::map<World::Scene*, SceneMeta> _sceneMeta;
		World::Scene* _sceneToSave;

	public:
		Editor(Common::Engine* engine, ComponentRegistry* registry = nullptr);
		~Editor();

	private:
        SceneMeta& GetSceneMeta(World::Scene* scene);
        void ShowSceneSaveAs(World::Scene* scene);

		static bool LoadImGuiImage(const char* filename, unsigned int* out_texture, int* out_width, int* out_height);
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
		void Input();
		void SaveDialogs();

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