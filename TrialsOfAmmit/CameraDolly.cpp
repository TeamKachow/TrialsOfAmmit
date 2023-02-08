#include "CameraDolly.h"

CameraDolly::CameraDolly(Hudson::Input::InputManager* inputRef) : Behaviour("CameraDollyBehaviour")
{
	_inputManager = inputRef;
}

CameraDolly::~CameraDolly()
{

}

void CameraDolly::OnCreate()
{
	_defaultCamera = new Hudson::Render::Camera(0.0f, 1600.0f, 900.0f, 0.0f, -50.0f, 50.0f);
	//_defaultCamera->SetPosition(vec3(0,0,0));
	GetEngine()->GetRenderer()->SetCamera(_defaultCamera);
}

void CameraDolly::OnDestroy()
{

}

void CameraDolly::OnTick(const double& dt)
{
	_defaultCamera->SetPosition(vec3(_parent->GetTransform().pos.x, _parent->GetTransform().pos.y,0));
#ifdef ENABLE_EDITOR
	if (_inputManager->getActionState("Arrowup"))
	{
		_parent->GetTransform().pos.y = _parent->GetTransform().pos.y - 100 * dt;
	}
	if (_inputManager->getActionState("ArrowDown"))
	{
		_parent->GetTransform().pos.y = _parent->GetTransform().pos.y + 100 * dt;

	}
	if (_inputManager->getActionState("ArrowLeft"))
	{
		_parent->GetTransform().pos.x = _parent->GetTransform().pos.x - 100 * dt;

	}
	if (_inputManager->getActionState("ArrowRight"))
	{
		_parent->GetTransform().pos.x = _parent->GetTransform().pos.x + 100 * dt;

	}
#endif

}

void CameraDolly::DrawPropertyUI()
{

}

void CameraDolly::FromJson(const nlohmann::json& j)
{

}

void CameraDolly::ToJson(nlohmann::json& j)
{

}