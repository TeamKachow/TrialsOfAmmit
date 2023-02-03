#pragma once
#include "../Util/stdafx.h"

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
    
}