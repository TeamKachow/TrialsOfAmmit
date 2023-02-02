#include "Debug.h"

#include <boost/stacktrace/stacktrace.hpp>
#include "../Common/Engine.h"

static void CreateDumpFile()
{
    Hudson::Common::Engine* engine = Hudson::Common::Engine::GetInstance();

    std::string formattedTime = std::format("{0:%F_%T}", std::chrono::system_clock::now());
    std::stringstream dumpName;
    dumpName << "crash_" << formattedTime << ".txt";
    std::ofstream dump(dumpName.str());
    
    Hudson::Util::Debug::LogError("Unexpected error! Stack trace:", dump);

    dump << "\n";
    dump << std::format("Engine: {}\n", static_cast<void*>(engine));
    dump << std::format("Scenes loaded: {} ({})\n", engine->GetSceneManager()->GetLoadedScenes().size(), static_cast<void*>(engine->GetSceneManager()));
}

void Hudson::Util::Debug::PrintStackTrace(std::ostream& output)
{
    output << boost::stacktrace::stacktrace();
}

void Hudson::Util::Debug::LogError(const std::string& msg, std::ostream& output)
{
    output << msg << "\n";
    PrintStackTrace();
}

void Hudson::Util::Debug::RegisterAbortHandler()
{
    std::set_terminate([]()
        {
            LogError("Unexpected error! Engine is exiting.");

            CreateDumpFile();
            std::abort();
        });
}
