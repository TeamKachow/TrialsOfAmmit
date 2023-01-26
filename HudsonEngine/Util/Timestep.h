#include "../Util/stdafx.h"

constexpr double FPS_60 = 1.0 / 60.0;

namespace  Hudson::Util
{
	class Timestep
	{
	public:
		Timestep();
		~Timestep();

		void CalculateTimestep();

		double DeltaTime;

		const double GetDeltaTime() { return DeltaTime; }

	public:
		double _lastTime;
		double _timer;
		double _accumulator;
		double _nowTime;
		int _frames;
		int _updates;
		std::function<void()> _doTick;
	};
}
