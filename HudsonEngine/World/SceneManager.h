#pragma once
#include <vector>

// forward declaration
namespace Hudson::World
{
    class Scene;
}

namespace Hudson::World
{
    class SceneManager
    {
    // TODO: all of this
    private:
        std::vector<Scene*> _loadedScenes; // TODO: map of ID to ptr?

    public:
        // get active scenes
        // get all scenes
        // load scene from file (string)
        // set scene active (bool)
        // destroy scene (scene*)
    };
}
