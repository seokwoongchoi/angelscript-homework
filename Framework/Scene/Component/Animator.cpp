#include "stdafx.h"
#include "Animator.h"

Animator::Animator(Context * context, GameObject * object, Transform * transform)
	: IComponent(context, object, transform)
	, animationMode(AnimationMode::Stop)
	, curClipNum(0)
	, frameTimer(0.0f)
	, currentAnimation(nullptr)
{
	timer = context->GetSubsystem<Timer>();
	resourceManager = context->GetSubsystem<ResourceManager>();
}

Animator::~Animator()
{
}

void Animator::OnInitialize()
{
}

void Animator::OnStart()
{
}

void Animator::OnUpdate()
{
	bool bCheck = true;
	bCheck &= currentAnimation != nullptr;
	bCheck &= animationMode == AnimationMode::Play;

	if (bCheck)
	{
		frameTimer += timer->GetDeltaTimeMs();

		if (frameTimer > currentAnimation->GetKeyframeFromIndex(curClipNum).time)
		{
			curClipNum++;

			switch (currentAnimation->GetRepeatType())
			{
			case AnimationRepeatType::Once:
				if (curClipNum >= currentAnimation->GetKeyframeCount())
				{
					curClipNum = currentAnimation->GetKeyframeCount() - 1;
					Pause();
				}
				break;
			case AnimationRepeatType::Loop:
				curClipNum %= currentAnimation->GetKeyframeCount();
				break;
			}

			frameTimer = 0.0f;
		}
	}
}

void Animator::OnStop()
{
}

void Animator::OnDestroy()
{
}

void Animator::OnSave()
{
}





const Keyframe & Animator::GetCurrentKeyframe()
{
	assert(currentAnimation);
	return currentAnimation->GetKeyframeFromIndex(curClipNum);
}

void Animator::SetCurrentAnimation(const string & animationName)
{
	assert(animationTable.count(animationName) > 0);
	currentAnimation = animationTable[animationName];
}

void Animator::AddAnimation(const string & filePath)
{
	auto animation =
		resourceManager->Load<Animation>(filePath);

	AddAnimation(animation);
}

void Animator::AddAnimation(Animation * animation)
{
	assert(animationTable.count(animation->GetResourceName()) < 1);
	animationTable[animation->GetResourceName()] = animation;
}

void Animator::Play()
{
	animationMode = AnimationMode::Play;
	frameTimer = 0.0f;
}

void Animator::Stop()
{
	animationMode = AnimationMode::Stop;
	frameTimer = 0.0f;
	curClipNum = 0;
}

void Animator::Pause()
{
	animationMode = AnimationMode::Pause;
}