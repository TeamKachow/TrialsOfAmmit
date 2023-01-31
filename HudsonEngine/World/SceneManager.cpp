#include "../World/SceneManager.h"
#include "../World/Scene.h"
#include "../Util/Timestep.h"

void Hudson::World::SceneManager::HandlePostTick()
{
    // Do queued updates to loaded scenes
    _scenes.Update();
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
    return _scenes.Get();
}

void Hudson::World::SceneManager::AddScene(Scene* scene)
{
    // Queue scene for addition
    _scenes.Add(scene);
    // If not ticking, update now
    if (!_isTicking)
    {
        _scenes.Update();
    }
}

void Hudson::World::SceneManager::RemoveScene(Scene* scene)
{
    // Queue scene for removal
    _scenes.Remove(scene);
    // If not ticking, update now
    if (!_isTicking)
    {
        _scenes.Update();
    }
}

bool Hudson::World::SceneManager::IsSceneLoaded(Scene* scene)
{
    return _scenes.Get().contains(scene);
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
    for (auto& scene : _scenes.Get())
    {
        scene->Tick(dt);
    }

    // Clear ticking flag
    _isTicking = false;
}
