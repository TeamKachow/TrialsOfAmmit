#pragma once
#include "../Util/stdafx.h"

namespace Hudson::World
{
    class Scene;
}

namespace Hudson::Render
{
    class Camera;
}

namespace Hudson::Util::Debug
{
    /**
     * \brief Print the current stack trace.
     */
    void PrintStackTrace(std::ostream& output = std::cerr);

    /**
     * \brief Log an error with a stacktrace.
     * \param msg The message to log.
     */
    void LogError(const std::string& msg, std::ostream& output = std::cerr);

    /**
     * \brief Register the engine's abort handler.
     */
    void RegisterAbortHandler();

    void DumpColliders(Hudson::World::Scene* scene, Hudson::Render::Camera* camera, std::ostream& out = std::cerr);
    
}