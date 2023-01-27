#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Util::Debug
{
    /**
     * \brief Print the current stack trace.
     */
    void PrintStackTrace();

    /**
     * \brief Log an error with a stacktrace.
     * \param msg The message to log.
     */
    void LogError(const std::string& msg);
    
}