#include <iostream>

#include <Hudson.h>

#include "DemoBehaviour.h"

Hudson::Common::Engine* engine;

#ifdef _DEBUG
#define ENABLE_EDITOR
#endif

#ifdef ENABLE_EDITOR
#pragma message("Creating an editor build")
#endif

#ifdef ENABLE_EDITOR
Hudson::Editor::Editor* editor;
#endif

Hudson::Render::Camera* _defaultCamera = new Hudson::Render::Camera(0.0f, 1600.0f, 900.0f, 0.0f, -50.0f, 50.0f);

Hudson::Render::TextComponent* Text1;
Hudson::Render::TextComponent* Text2;

Hudson::Render::SpriteComponent* Sprite1;
Hudson::Render::SpriteComponent* Sprite2;
Hudson::Physics::PhysicsComponent* Physics1;
Hudson::Physics::PhysicsComponent* Physics2;
Hudson::Physics::ColliderComponent* Collider1;
Hudson::Physics::ColliderComponent* Collider2;

// TODO: this *needs* to move to Hudson ASAP
Hudson::Common::ResourceManager* resManager;

void InitRegistry()
{
    Hudson::Common::ComponentRegistry* registry = engine->GetComponentRegistry();
    registry->RegisterEngineComponents();

    registry->Register<DemoBehaviour>("Demo Behaviour");
}

void Init() 
{
    Hudson::Util::Debug::RegisterAbortHandler();

    Hudson::Common::ResourceManager::SetupInstance(); // Set up single resource manager (TODO: decide per-scene/per-game)
    resManager = Hudson::Common::ResourceManager::GetInstance();
    engine = new Hudson::Common::Engine();

#ifdef ENABLE_EDITOR
    editor = new Hudson::Editor::Editor(engine);
#endif

    engine->Setup();
    InitRegistry();
    
    engine->GetRenderer()->SetupDefaultShaders();

#ifdef ENABLE_EDITOR
    engine->GetInputManager()->SetEditorRef(editor);
    engine->GetSceneManager()->SetPaused(true);
#endif
}

void Hello(bool& isActive)
{
    std::cout << "Hello" << std::endl;
}


void GameSetup()
{
    // Set up default camera
    _defaultCamera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    engine->GetRenderer()->SetCamera(_defaultCamera);

    //glfwSetWindowSize(engine->GetRenderer()->GetWindow()->GetWindow(), 1920, 1080);
    //engine->GetRenderer()->CreateFramebuffers(1920, 1080);

    // Load textures
    resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");

	#ifdef ENABLE_EDITOR
    ToolData toolData;
    toolData.function = Hello;
    toolData.isRepeatingFunction = false;
    editor->AddTool("Hello", toolData);
	#endif


    // Create scene
    {

        Sprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
        Sprite1->SetGridSize(glm::vec2(3, 4));
        Sprite1->SetDepthOrder(1);

        Sprite2 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
        Sprite2->SetGridSize(glm::vec2(3, 4));
        Sprite2->SetDepthOrder(2);

        Physics1 = new Hudson::Physics::PhysicsComponent();
        Physics1->SetMass(1.0f);
        Physics1->SetForce(glm::vec2(10.0, 0));
        Physics1->SetAcceleration(glm::vec2(100, 0), true);
        Physics1->SetVelocity(glm::vec2(100, 0));

        Physics2 = new Hudson::Physics::PhysicsComponent();
        Physics2->SetMass(1.0f);
        Physics2->SetForce(glm::vec2(-10.0, 0));
        Physics2->SetAcceleration(glm::vec2(-100, 0), true);
        Physics2->SetVelocity(glm::vec2(-100, 0));

        Collider1 = new Hudson::Physics::ColliderComponent();
        Collider2 = new Hudson::Physics::ColliderComponent();

        Text1 = new Hudson::Render::TextComponent("../DemoGame/Fonts/arial.ttf", resManager->GetShader("textShader"));
        Text1->SetText("the quick brown fox jumps over the lazy dog");
        Text1->SetColor(glm::vec3(0.5, 0.8f, 0.2f));

        Text2 = new Hudson::Render::TextComponent("../DemoGame/Fonts/arial.ttf", resManager->GetShader("textShader"));
        Text2->SetText("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
        Text2->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

        // Load initial scene from file 
        // TODO: Hudson::World::Scene* startScene = engine->GetSceneManager()->LoadScene("menu.scene");
        // TODO: startScene.resManager.loadTexture, startScene.resManager.loadShader etc - Brandon B
        Hudson::World::Scene* startScene = new Hudson::World::Scene();
        engine->GetSceneManager()->AddScene(startScene);

        Hudson::Entity::GameObject* blah = new Hudson::Entity::GameObject();
        blah->AddComponent(Sprite1);
        blah->AddComponent(new DemoBehaviour(Sprite1));
        blah->AddComponent(Physics1);
        blah->AddComponent(Collider1);
        startScene->AddObject(blah);

        blah->GetTransform().pos.x = 64.0f;
        blah->GetTransform().pos.y = 0.0f;

        Hudson::Entity::GameObject* blah2 = new Hudson::Entity::GameObject();
        blah2->AddComponent(Sprite2);
        //blah2->AddComponent(new DemoBehaviour(Sprite2));
        blah2->AddComponent(Physics2);
        blah2->AddComponent(Collider2);
        startScene->AddObject(blah2);

        blah2->GetTransform().pos.x = 1280.0f;
        blah2->GetTransform().pos.y = 128.0f;

        Hudson::Entity::GameObject* hud = new Hudson::Entity::GameObject();
        hud->SetName("Text");
        hud->AddComponent(Text1);
        Hudson::Entity::GameObject::Transform transform = { glm::vec2(0,100), glm::vec2(1,1), 0 };
        hud->SetTransform(transform);
        startScene->AddObject(hud);

        Hudson::Entity::GameObject* hud2 = new Hudson::Entity::GameObject();
        hud2->SetName("Text");
        hud2->AddComponent(Text2);
        transform = { glm::vec2(0,200), glm::vec2(1,1), 0 };
        hud2->SetTransform(transform);
        startScene->AddObject(hud2);

        
    }

    std::cout << "DemoGame: engine has been set up!\n";
}


int main() {
    Init();

    // Set up game scene/resources
    GameSetup();

    // Run engine loop until it is shut down
    engine->Run();


    // Clean up
    engine->Cleanup();
    delete engine;
}
