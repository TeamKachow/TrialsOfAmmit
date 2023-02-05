
#pragma once

#include <map>
#include <string>

class Scene;

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void addScene(const std::string& name, Scene* scene);
    void setActiveScene(const std::string& name);
    Scene* getActiveScene();

private:
    std::map<std::string, Scene*> scenes;
    Scene* activeScene;
};