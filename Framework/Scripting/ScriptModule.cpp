#include "stdafx.h"
#include "ScriptModule.h"
#include <AngelScript\scriptbuilder\scriptbuilder.cpp>

ScriptModule::ScriptModule(Scripting * scriptEngine, const string & moduleName)
	: scriptEngine(scriptEngine)
	, moduleName(moduleName)
	, builder(nullptr)
{
}

ScriptModule::~ScriptModule()
{
	scriptEngine->DiscardModule(moduleName);
	SAFE_DELETE(builder);
}

const bool ScriptModule::LoadScript(const string & filePath)
{
	if (!builder)
		builder = new CScriptBuilder();

	int result = builder->StartNewModule
	(
		scriptEngine->GetAsIScriptEngine(),
		moduleName.c_str()
	);
	assert(result >= 0);

	result = builder->AddSectionFromFile(filePath.c_str());
	assert(result >= 0);

	result = builder->BuildModule();
	assert(result >= 0);

	return true;
}

asIScriptModule * ScriptModule::GetAsIScriptModule()
{
	return builder->GetModule();
}
