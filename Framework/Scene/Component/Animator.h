#pragma once
#include "IComponent.h"

class Animator : public IComponent
{
public:
	Animator
	(
		class Context* context,
		class GameObject* object,
		class Transform* transform
	);
	virtual ~Animator();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;
	void OnSave()override;
	

	Animation* GetCurrentAnimation() const { return currentAnimation; }
	const Keyframe& GetCurrentKeyframe();

	void SetCurrentAnimation(const string& animationName);

	void AddAnimation(const string& filePath);
	void AddAnimation(Animation* animation);

	void Play();
	void Stop();
	void Pause();

	const bool IsPlaying() { return animationMode == AnimationMode::Play ? true : false; }
	const bool IsStop() { return animationMode == AnimationMode::Stop ? true : false; }
	const bool IsPause() { return animationMode == AnimationMode::Pause ? true : false; }

private:
	enum class AnimationMode : uint
	{
		Play,
		Stop,
		Pause
	};

private:
	class ResourceManager* resourceManager;
	class Timer* timer;

	AnimationMode animationMode;
	uint curClipNum;
	float frameTimer;

	Animation* currentAnimation;
	map<string, Animation*> animationTable;
};