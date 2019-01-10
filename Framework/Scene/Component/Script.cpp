#include "stdafx.h"
#include "Script.h"
#include "../../Scripting/ScriptInstance.h"

Script::Script(Context * context, GameObject * object, Transform * transform)
	: IComponent(context, object, transform)
	, scriptInstance(nullptr)
	, bStopped(true)
{
}

Script::~Script()
{
	SAFE_DELETE(scriptInstance);
}

void Script::OnInitialize()
{
}

void Script::OnStart()
{
	if (!scriptInstance)
		return;

	if (!scriptInstance->IsInstantiated())
		return;

	scriptInstance->ExcuteStart();
	bStopped = false;
}

void Script::OnUpdate()
{
	if (bStopped)
		return;

	if (!scriptInstance)
		return;

	if (!scriptInstance->IsInstantiated())
		return;

	scriptInstance->ExcuteUpdate();
}

void Script::OnStop()
{
	bStopped = true;
}

void Script::OnDestroy()
{
}

void Script::OnSave()
{
}




const string Script::GetScriptPath()
{
	return scriptInstance ? scriptInstance->GetScriptPath() : "";
}

const string Script::GetName()
{
	return scriptInstance ? FileSystem::GetIntactFileNameFromPath(GetScriptPath()) : "";
}

const bool Script::SetScript(const string & filePath)
{
	scriptInstance = new ScriptInstance();

	bool bResult = scriptInstance->Instantiate
	(
		filePath,
		object,
		context->GetSubsystem<Scripting>()
	);
	assert(bResult);

	if (!scriptInstance->IsInstantiated())
		return false;

	return true;
}
