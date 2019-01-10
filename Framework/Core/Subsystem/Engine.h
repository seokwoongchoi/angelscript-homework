#pragma once
#include "ISubsystem.h"

enum EngineFlags : unsigned long
{
	EngineFlags_Update	= 1UL << 0,
	EngineFlags_Render	= 1UL << 1,
	EngineFlags_Game	= 1UL << 2,
};

class Engine : public ISubsystem
{
public:
	static const unsigned long& GetEngineFlags() { return engineFlags; }
	static void SetEngineFlags(const unsigned long& flags) { engineFlags = flags; }
	static void OnEngineFlags(const EngineFlags& flags) { engineFlags |= flags; }
	static void OffEngineFlags(const EngineFlags& flags) { engineFlags &= ~flags; }
	static void ToggleEngineFlags(const EngineFlags& flags) { engineFlags = !IsOnEngineFlags(flags) ? engineFlags | flags : engineFlags & ~flags; }
	static const bool IsOnEngineFlags(const EngineFlags& flags) { return (engineFlags & flags) > 0UL; }

public:
	Engine(class Context* context);
	virtual ~Engine();

	const bool Initialize() override;
	void Update();

private:
	static unsigned long engineFlags;

	class Timer* timer;
	class Input* input;
	class SceneManager* sceneManager;
	class Renderer* renderer;
};