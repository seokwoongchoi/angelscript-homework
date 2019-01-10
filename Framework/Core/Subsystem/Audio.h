#pragma once
#include "ISubsystem.h"

class Audio : public ISubsystem
{
public:
	Audio(class Context* context);
	virtual ~Audio();

	FMOD::System* GetFMODSystem() const { return system; }

	const bool Initialize() override;
	void Update();

private:
	FMOD::System* system;
	int maxChannel;
	float distanceFactor;
	int result;
	bool bInitialized;
};