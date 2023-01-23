#pragma once
#include "Camera.h"
#include "stdafx.h"
#include "Render/Shader.h"


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

        // Render to Texture
        Shader* screenShader;

        unsigned int screenVertexArrayObject;
        unsigned int frameBufferObject;
        unsigned int textureColorBuffer;

    public:
        Renderer(Common::Engine* engine);
        ~Renderer();

        void StartImGui();

        void InitRenderToTexture(int screenWidth, int screenHeight);

        void Draw();
        void WaitForRender();


    };
}

