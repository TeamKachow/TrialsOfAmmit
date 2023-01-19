#pragma once
#include "Camera.h"

namespace Hudson::Common
{
    class Engine;
}

namespace Hudson::Render
{
    class Window;

    class Renderer
    {
        Common::Engine* _engine;

        std::unique_ptr<Window> _window;
        Camera _defaultCamera;

    public:
        Renderer(Common::Engine* engine);
        ~Renderer();

        void Draw();
        void WaitForRender();
    };
}

