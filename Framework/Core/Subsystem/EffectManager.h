#pragma once
#include "ISubsystem.h"

class EffectManager : public ISubsystem
{
public:
	EffectManager(class Context* context);
	virtual ~EffectManager();

	void AddEffect
	(
		const string& effectFilePath,
		const Vector3& position,
		const Vector3& scale = Vector3(1, 1, 1)
	);

	void AddEffect
	(
		const string& textureFilePath,
		const string& animationFilePath,
		const Vector3& position,
		const Vector3& scale = Vector3(1, 1, 1)
	);

	void Initialize() override {}
	void Update() override;
	void Render();

private:
	vector<class Effect*> effects;
};