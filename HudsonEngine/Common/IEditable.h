#pragma once

namespace Hudson::Common
{
    class IEditable
    {
    public:
        virtual void DrawPropertyUI() = 0;
    };
}
