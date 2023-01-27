#include "Timestep.h"

Hudson::Util::Timestep::Timestep(std::function<void(double dt)> doTick) : _doTick(doTick)
{
	_lastTime = glfwGetTime();
	_timer = _lastTime;
	_accumulator = 0;
	_nowTime = 0;
	_frames = 0;
	_updates = 0;
	DeltaTime = 0;
}

Hudson::Util::Timestep::~Timestep()
{
}

void Hudson::Util::Timestep::CalculateTimestep()
{
	_nowTime = glfwGetTime();
	_accumulator += ((_nowTime - _lastTime) / FPS_60);
	_lastTime = _nowTime;

	while (_accumulator >= 1.0)
	{
        DeltaTime = FPS_60;
        _doTick(DeltaTime);
        _updates++;
		_accumulator--;
	}

	// Renders at maximum possible _frames - Render Here
	_frames++;

	// Reset after one second
	if (glfwGetTime() - _timer > 1.0)
	{
		_timer++;
		std::cout << "FPS: " << _updates << std::endl;
		_updates = 0;
		_frames = 0;
	}

}
