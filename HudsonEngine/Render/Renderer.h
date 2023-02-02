#pragma once
#include "../Util/stdafx.h"
#include "../Render/Shader.h"
#include  "../Render/Camera.h"

namespace Hudson::Common
{
    class Engine;
}

namespace Hudson::Render
{
    class Window;

    class Renderer
    {
    private:
        Common::Engine* _engine;
        std::unique_ptr<Window> _window;
        Render::Camera* _camera;

        // Debug
        double lastTime;
        double nowTime;

        double deltaTime;

        //double updates++;

        // Render to Texture
        Shader* screenShader = nullptr;

        unsigned int screenVertexArrayObject;
        unsigned int frameBufferObject;
        unsigned int textureColorBuffer;

        bool _imguiDockspace;

        // Freetype
        FT_Library _ft;
        FT_Face _face;

        void UpdateSetShaders();

    public:
        Renderer(Common::Engine* engine);
        ~Renderer();

        void StartImGui();

        void InitRenderToTexture();
        void CreateFramebuffers(unsigned int extentWidth, unsigned int extentHeight);

        Window* GetWindow() { return _window.get(); }
        unsigned int GetRenderedSceneTexture() { return textureColorBuffer; }

        Render::Camera* GetCamera() const  {return _camera;}
        void SetCamera(Render::Camera* const camera) { _camera = camera;}

        void Draw();
        void WaitForRender();

        void SetImguiDockspace(bool enabled);
    };
}

