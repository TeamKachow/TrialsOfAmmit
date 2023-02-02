#include "BaseAbilityClass.h"

//BaseAbilityClass::BaseAbilityClass(Hudson::Render::SpriteComponent* spriteComponent, int cooldown, int active_time) : Behaviour ("Ability")
//BaseAbilityClass::BaseAbilityClass(int cooldown, int active_time) : Behaviour ("Ability")
//{
//	//Values of all the variables *
//	_cooldownTime = cooldown;
//	_activeTime = active_time;
//}

// Deal with all this shit later ^^^

BaseAbilityClass::BaseAbilityClass() : Behaviour ("AbilityBehaviour")
{
	//Values of all the variables *
}

BaseAbilityClass::~BaseAbilityClass()
{
}

void BaseAbilityClass::OnCreate() //Make sure to set things up in order
{
}

void BaseAbilityClass::OnTick(const double& dt) //Update
{
}

void BaseAbilityClass::OnDestroy() 
{
}

void BaseAbilityClass::DrawPropertyUI() //Imgui Stuff
{
}

