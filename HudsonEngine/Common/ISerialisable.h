#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Common
{
    class ISerialisable
    {
    public:
        virtual uint32_t GetSerialID() = 0;
    };
}
