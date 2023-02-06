#include "../World/SceneManager.h"
#include "../World/Scene.h"
#include "../Util/Timestep.h"

Hudson::World::SceneManager::SceneManager()
{
    _time = new Hudson::Util::Timestep([&](const double dt)
        {
            for (auto& scene : _scenes.Get())
            {
                scene->Tick(dt);
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
    nlohmann::json jsonIn = nlohmann::json::parse(file);

    Scene* scene = new Scene(jsonIn.get<Scene>());

    return scene;
}

void Hudson::World::SceneManager::SaveScene(const std::string& path, Scene* scene)
{
    std::ofstream file(path);
    nlohmann::json jsonOut = *scene;
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
