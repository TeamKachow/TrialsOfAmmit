#include "Debug.h"
#include <boost/stacktrace/stacktrace.hpp>

void Hudson::Util::Debug::PrintStackTrace()
{
    std::cerr << boost::stacktrace::stacktrace();
}

void Hudson::Util::Debug::LogError(const std::string& msg)
{
    std::cerr << msg << "\n";
    PrintStackTrace();
}
