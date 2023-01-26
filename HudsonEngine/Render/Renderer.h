#pragma once
#include "../Entity/Camera.h"
#include "../Util/stdafx.h"

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

        void* sceneRenderTexture;

        Camera _defaultCamera;

    public:
        Renderer(Common::Engine* engine);
        ~Renderer();

        void StartImGui();

        void Draw();
        void WaitForRender();

        GLFWwindow* GetWindow();
    };
}

