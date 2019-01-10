#pragma once
#include "IComponent.h"

class Script : public IComponent
{
public:
	Script
	(
		class Context* context,
		class GameObject* object,
		class Transform* transform
	);
	virtual ~Script();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;
	void OnSave()override;
	

	const string GetScriptPath();
	const string GetName();

	const bool SetScript(const string& filePath);

private:
	class ScriptInstance* scriptInstance;
	bool bStopped;
};