#pragma once
#include <GLFW/glfw3.h>	
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool getKeyInput(GLFWwindow* window, string action);
	void setKeyEvent(string action, string keyName);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
	map<string, int> keys;
	map<string, int> keyActions;
	map<int, bool> keyDown;
	static vector<InputManager*> instances;

	void initialiseKeys();
	void setKeyDown(int key, bool isDown);
};

