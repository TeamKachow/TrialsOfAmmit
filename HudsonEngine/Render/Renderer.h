#pragma once
#include "../Util/stdafx.h"
#include "../Render/Shader.h"

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

        // Debug
        double lastTime;
        double nowTime;

        double deltaTime;

        //double updates++;

        // Render to Texture
        Shader* screenShader;

        unsigned int screenVertexArrayObject;
        unsigned int frameBufferObject;
        unsigned int textureColorBuffer;

        bool _imguiDockspace;

    public:
        Renderer(Common::Engine* engine);
        ~Renderer();

        void StartImGui();

        void InitRenderToTexture();
        void CreateFramebuffers(unsigned int extentWidth, unsigned int extentHeight);

        Window* GetWindow() { return _window.get(); }
        unsigned int GetRenderedSceneTexture() { return textureColorBuffer; }

        void Draw();
        void WaitForRender();

        void SetImguiDockspace(bool enabled);
    };
}

