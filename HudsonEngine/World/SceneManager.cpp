#include "../World/SceneManager.h"
#include "../World/Scene.h"
#include "../Util/Timestep.h"

Hudson::World::SceneManager::SceneManager()
{
    _time = new Hudson::Util::Timestep([&](const double dt)
        {
            for (auto& scene : _scenes.Get())
            {
                if (_paused)
                {
                    scene->UpdateDeferredObjects();
                }
                else
                {
                    scene->Tick(dt);
                }
            }
        });
}

Hudson::World::SceneManager::~SceneManager()
{

}

void Hudson::World::SceneManager::HandlePostTick()
{
    // Do queued updates to loaded scenes
    _scenes.Update();
}

Hudson::World::Scene* Hudson::World::SceneManager::LoadScene(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        return nullptr;
    }

    nlohmann::json jsonIn = nlohmann::json::parse(file);
    Scene* scene = new Scene();
    scene->FromJson(jsonIn);

    return scene;
}

void Hudson::World::SceneManager::SaveScene(const std::string& path, Scene* scene)
{
    std::filesystem::path parentDir = std::filesystem::path(path).parent_path();
    if (!std::filesystem::exists(parentDir))
    {
        std::filesystem::create_directories(parentDir);
    }

    std::ofstream file(path);
    nlohmann::json jsonOut;
    scene->ToJson(jsonOut);
    file << jsonOut.dump(2);
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
	// We should never EVER call this method recursively
    assert(!_isTicking);

    // Set ticking flag
    _isTicking = true;

    // Tick active scenes
    _time->CalculateTimestep();

    // Clear ticking flag
    _isTicking = false;
}

bool Hudson::World::SceneManager::IsPaused() const
{
    return _paused;
}

void Hudson::World::SceneManager::SetPaused(bool paused)
{
    _paused = paused;
}
