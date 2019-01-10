#pragma once
#include "IResource.h"

enum class AnimationRepeatType : uint
{
	Once, Loop
};

struct Keyframe
{
	Texture* texture;
	Vector2 offset;
	Vector2 size;
	float time;
};

class Animation : public IResource
{
public:
	Animation(class Context* context);
	virtual ~Animation();

	const AnimationRepeatType& GetRepeatType() const { return repeatType; }
	const Keyframe& GetKeyframeFromIndex(const uint& index);
	const uint GetKeyframeCount() const { return keyframes.size(); }
	vector<Keyframe> GetKeyframes() {return keyframes;}

	void SetRepeatType(const AnimationRepeatType& repeatType) { this->repeatType = repeatType; }

	void AddKeyframe(const Keyframe& keyframe);

	virtual void SaveToFile(const string& saveFilePath) override;
	virtual void LoadFromFile(const string& loadFilePath) override;

private:
	AnimationRepeatType repeatType;
	vector<Keyframe> keyframes;
};