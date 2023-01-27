#include "../World/SceneManager.h"
#include "../World/Scene.h"

void Hudson::World::SceneManager::HandlePostTick()
{
    Scene* found = nullptr;

    for (Scene* toDelete : _toRemove)
    {
        auto iter = std::ranges::find(_loadedScenes, toDelete);
        assert(iter != _loadedScenes.end());
        _loadedScenes.erase(iter);
        // TODO: determine the correct way/time to delete from memory
        delete toDelete;
    }
    _toRemove.clear();

    // TODO: toAdd
}

Hudson::World::Scene* Hudson::World::SceneManager::LoadScene(const std::string& path)
{
    std::ifstream file(path);
    // todo: cereal archive

    return nullptr;
}

void Hudson::World::SceneManager::SaveScene(const std::string& path, Scene* scene)
{
    std::ofstream file(path);
    // TODO: cereal archive
}

const std::set<Hudson::World::Scene*> Hudson::World::SceneManager::GetLoadedScenes()
{
    return _loadedScenes;
}

void Hudson::World::SceneManager::AddScene(Scene* scene)
{
    if (_isTicking)
    {
        // If we're currently ticking the scene, queue the scene to be added
        _toAdd.emplace(scene);
    }
    else
    {
        // If we're not currently ticking the scene, add the scene immediately
        _loadedScenes.emplace(scene);
    }
}

void Hudson::World::SceneManager::RemoveScene(Scene* scene)
{
    if (_isTicking)
    {
        // If we're currently ticking the scene, queue the scene to be removed
        _toRemove.emplace(scene);
    }
    else
    {
        // If we're not currently ticking the scene, remove the scene immediately
        _loadedScenes.erase(scene);
    }
}

bool Hudson::World::SceneManager::IsSceneLoaded(Scene* scene)
{
    return std::ranges::find(_loadedScenes, scene) != _loadedScenes.end();
}

void Hudson::World::SceneManager::Tick()
{
    // TODO: use staffs's Time class for fixed timestep
    const double dt = 1.0 / 60.0;

    // We should never EVER call this method recursively
    assert(!_isTicking);

    // Set ticking flag
    _isTicking = true;

    // Tick active scenes
    for (auto& scene : _loadedScenes)
    {
        scene->Tick(dt);
    }

    // Clear ticking flag
    _isTicking = false;
}
