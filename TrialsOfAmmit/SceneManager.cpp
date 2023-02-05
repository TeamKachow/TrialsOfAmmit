#include <iostream>
#include <unordered_map>
#include "Scene.h"

class SceneManager
{
private:
    std::unordered_map<std::string, Scene*> scenes;
    Scene* currentScene;

public:
    SceneManager()
    {
        currentScene = nullptr;
    }

    ~SceneManager()
    {
        for (auto& scene : scenes)
        {
            delete scene.second;
        }
        scenes.clear();
    }

    void addScene(const std::string& name, Scene* scene)
    {
        scenes[name] = scene;
    }

    void setScene(const std::string& name)
    {
        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            currentScene = it->second;
        }
        else
        {
            std::cerr << "Scene not found: " << name << std::endl;
        }
    }

    Scene* getCurrentScene() const
    {
        return currentScene;
    }

    void update()
    {
        if (currentScene != nullptr)
        {
            currentScene->update();
        }
    }

    void render()
    {
        if (currentScene != nullptr)
        {
            currentScene->render();
        }
    }
};

