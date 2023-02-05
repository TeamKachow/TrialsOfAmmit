#include "Debug.h"

#include <boost/stacktrace/stacktrace.hpp>
#include "../Common/Engine.h"

static void CreateDumpFile()
{
    Hudson::Common::Engine* engine = Hudson::Common::Engine::GetInstance();

    std::string formattedTime = std::format("{0:%F_%H-%M-%S}", std::chrono::system_clock::now());
    std::stringstream dumpName;
    dumpName << "crash_" << formattedTime << ".txt";
    std::ofstream dump(dumpName.str());

    std::cout << "\n\n";

    if (!dump.is_open())
    {
        std::cout << "Couldn't open " << dumpName.str() << " - not writing a crash dump";
        return;
    }

    std::cout << "Writing crash dump to " << dumpName.str() << "...\n";

    Hudson::Util::Debug::LogError("Unexpected error! \n\nStack trace:", dump);

    dump << "\n";
    dump << std::format("Engine: {}\n", static_cast<void*>(engine));
    dump << std::format("Scenes loaded: {} ({})\n", engine->GetSceneManager()->GetLoadedScenes().size(), static_cast<void*>(engine->GetSceneManager()));

    dump.close();

    std::cout << "Dump saved.\n";
}

void Hudson::Util::Debug::PrintStackTrace(std::ostream& output)
{
    output << boost::stacktrace::stacktrace();
}

void Hudson::Util::Debug::LogError(const std::string& msg, std::ostream& output)
{
    output << msg << "\n";
    PrintStackTrace(output);
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
