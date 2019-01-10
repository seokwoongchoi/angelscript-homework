#include "stdafx.h"
#include "ScriptInstance.h"
#include "ScriptModule.h"
#include <AngelScript\angelscript.h>
#include "../Scene/GameObject.h"

ScriptInstance::ScriptInstance()
	: constructorFunction(nullptr)
	, startFunction(nullptr)
	, updateFunction(nullptr)
	, scriptObject(nullptr)
	, scriptModule(nullptr)
	, scriptEngine(nullptr)
	, bInstantiated(false)
{
}

ScriptInstance::~ScriptInstance()
{
	if (scriptObject)
	{
		scriptObject->Release();
		scriptObject = nullptr;
	}

	constructorFunction = nullptr;
	startFunction = nullptr;
	updateFunction = nullptr;
	scriptEngine = nullptr;
	bInstantiated = false;
}

const bool ScriptInstance::Instantiate(const string & path, GameObject * object, Scripting * scriptEngine)
{
	if (!object)
		return false;

	this->scriptEngine = scriptEngine;
	this->scriptPath = path;
	this->object = object;
	this->className = FileSystem::GetIntactFileNameFromPath(scriptPath);
	this->moduleName = className + object->GetName();
	this->constructorDeclaration = className + " @" + className + "(GameObject @)";

	bInstantiated = CreateScriptObject();
	return bInstantiated;
}

void ScriptInstance::ExcuteStart()
{
	scriptEngine->ExecuteCall(startFunction, scriptObject);
	
}

void ScriptInstance::ExcuteUpdate()
{
	scriptEngine->ExecuteCall(updateFunction, scriptObject);
}

const bool ScriptInstance::CreateScriptObject()
{
	//Create ScriptModule
	scriptModule = new ScriptModule(scriptEngine, moduleName);
	bool bResult = scriptModule->LoadScript(scriptPath);
	if (!bResult)
		return false;

	//Get Type
	auto type_id = scriptModule->GetAsIScriptModule()->GetTypeIdByDecl(className.c_str());
	asITypeInfo* type = scriptEngine->GetAsIScriptEngine()->GetTypeInfoById(type_id);
	if (!type)
		return false;

	//Get Function in the Script
	startFunction = type->GetMethodByDecl("void Start()");
	updateFunction = type->GetMethodByDecl("void Update()");
	constructorFunction = type->GetFactoryByDecl(constructorDeclaration.c_str());
	assert(constructorFunction);

	asIScriptContext* ctx = scriptEngine->RequestContext();
	int result = ctx->Prepare(constructorFunction);
	if (result < 0)
		return false;

	result = ctx->SetArgObject(0, object);
	if (result < 0)
		return false;

	result = ctx->Execute();
	if (result < 0)
		return false;

	scriptObject = *static_cast<asIScriptObject**>(ctx->GetAddressOfReturnValue());
	scriptObject->AddRef();

	scriptEngine->ReturnContext(ctx);
	
	return true;
}
