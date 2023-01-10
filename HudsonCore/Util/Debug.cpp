#include "Debug.h"
#include <iostream>
#include <boost/stacktrace/stacktrace.hpp>

void Hudson::Util::Debug::PrintStackTrace()
{
    std::cerr << boost::stacktrace::stacktrace();
}
