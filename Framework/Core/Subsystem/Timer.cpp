#include "stdafx.h"
#include "Timer.h"

Timer::Timer(Context * context)
	: ISubsystem(context)
	, deltaTimeMs(0.0f)
	, deltaTimeSec(0.0f)
{
}

Timer::~Timer()
{
}

const bool Timer::Initialize()
{
	prevTime = chrono::high_resolution_clock::now();
	return true;
}

void Timer::Update()
{
	auto curTime = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> ms = curTime - prevTime;
	prevTime = curTime;

	deltaTimeMs = static_cast<float>(ms.count());
	deltaTimeSec = static_cast<float>(ms.count() * 0.001);
}
