#pragma once
#include <Hudson.h>

using namespace std;
using namespace glm;

class CameraDolly : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	CameraDolly(Hudson::Input::InputManager* inputRef = {nullptr});
	~CameraDolly();
protected:

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;
	Hudson::Render::Camera* _defaultCamera;
	Hudson::Input::InputManager* _inputManager;
	const vec3 i = vec3(100, 100, 100);

};

