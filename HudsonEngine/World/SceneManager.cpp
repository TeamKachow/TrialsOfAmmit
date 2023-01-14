#include "SceneManager.h"
#include "Scene.h"

#include <assert.h>
#include <fstream>

void Hudson::World::SceneManager::HandlePostTick()
{
    Scene* found = nullptr;
    
    for (Scene* toDelete : _toDelete)
    {
        auto iter = std::ranges::find(_loadedScenes, toDelete);
        assert(iter != _loadedScenes.end());
        _loadedScenes.erase(iter);
        // TODO: determine the correct way/time to delete from memory
        delete toDelete;
    }
    _toDelete.clear();
}

Hudson::World::Scene* Hudson::World::SceneManager::LoadScene(const std::string& path)
{
    std::ifstream file(path);
    // todo: cereal archive
}

Hudson::World::Scene* Hudson::World::SceneManager::SaveScene(const std::string& path)
{
    std::ofstream file(path);
    // TODO: cereal archive
}

std::vector<Hudson::World::Scene*> Hudson::World::SceneManager::GetLoadedScenes()
{
}

void Hudson::World::SceneManager::AddScene(Scene* scene)
{
}

void Hudson::World::SceneManager::RemoveScene(Scene* scene)
{
}

bool Hudson::World::SceneManager::IsSceneLoaded(Scene* scene)
{
    return std::ranges::find(_loadedScenes, scene) != _loadedScenes.end();
}

void Hudson::World::SceneManager::Tick(const float dt)
{
}
