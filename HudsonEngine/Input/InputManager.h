#pragma once
#include "../Util/stdafx.h"
#include "../Render/Renderer.h"
#include "../Editor/Editor.h"
#include <iostream>
#include <cstring>
#include "json.hpp"

struct Key
{
	std::string keyName;
	std::vector<std::string> keyActions;
	int keyID;
	bool keyDown;
};

namespace Hudson::Input
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		std::vector<std::string> getKeyActions(std::string keyName);
		void setKeyEvent(std::string action, std::string keyName);
		void delKeyEvent(std::string action, std::string keyName);

		bool getActionState(std::string action);
		bool getM1Click() { return m1Click; }
		bool getM2Click() { return m2Click; }
		glm::vec2 getWorldMPos() { return glm::vec2(worldMouseXpos, worldMouseYpos); };
		glm::vec2 getScreenMPos() { return glm::vec2(screenMouseXpos, screenMouseYpos); }

		void Setup(Hudson::Render::Renderer* renderer);
		void SetEditorRef(Hudson::Editor::Editor* editorReference) { editorRef = editorReference; }

		void setDownTemp(std::string keyName);

		void LoadJSON();
		void WriteToJSON();

		static void BindCallbacks(GLFWwindow* window);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void cursorClickCallback(GLFWwindow* window, int button, int action, int mods);


	private:
		std::vector<Key> keys;
		bool m1Click;
		bool m2Click;
		double screenMouseXpos;
		double screenMouseYpos;

		float worldMouseXpos;
		float worldMouseYpos;

		static std::vector<InputManager*> instances;
		Hudson::Render::Renderer* renderRef;

		Hudson::Editor::Editor* editorRef;


		void initialiseKeys();
		void setKeyDown(int key, bool isDown);
		void setScreenCursorPos(double xPos, double yPos);
		void setWorldCursorPos(GLFWwindow* window, glm::mat4 inverseProjMat);
		void setM1Click(bool isDown);
		void setM2Click(bool isDown);
	};
}


