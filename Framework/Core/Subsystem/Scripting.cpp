#include "stdafx.h"
#include "Scripting.h"
#include <AngelScript\angelscript.h>
#include <AngelScript\scriptstdstring\scriptstdstring.cpp>
#include "../../Scripting/ScriptInterface.h"

Scripting::Scripting(Context * context)
	: ISubsystem(context)
	, scriptEngine(nullptr)
{
}

Scripting::~Scripting()
{
	Clear();

	if (scriptEngine)
	{
		scriptEngine->ShutDownAndRelease();
		scriptEngine = nullptr;
	}
}

const bool Scripting::Initialize()
{
	scriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	assert(scriptEngine);

	RegisterStdString(scriptEngine);

	auto scriptInterface = new ScriptInterface();
	scriptInterface->Register(context, scriptEngine);

	scriptEngine->SetMessageCallback
	(
		asMETHOD(Scripting, Message_CallBack),
		this,
		asCALL_THISCALL
	);

	scriptEngine->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES, true);

	SAFE_DELETE(scriptInterface);

	return true;
}

asIScriptEngine * Scripting::GetAsIScriptEngine()
{
	return scriptEngine;
}

asIScriptContext * Scripting::RequestContext()
{
	asIScriptContext* ctx = nullptr;
	if (ctxs.size())
	{
		ctx = *ctxs.rbegin();
		ctxs.pop_back();
	}
	else
		ctx = scriptEngine->CreateContext();

	return ctx;
}

void Scripting::ReturnContext(asIScriptContext * ctx)
{
	assert(ctx);
	ctxs.push_back(ctx);
	ctx->Unprepare();
}

const bool Scripting::ExecuteCall(asIScriptFunction * scriptFunc, asIScriptObject * obj)
{
	asIScriptContext* ctx = RequestContext();

	ctx->Prepare(scriptFunc);
	ctx->SetObject(obj);
	
	int result = ctx->Execute();

	if (result == asEXECUTION_EXCEPTION)
	{
		LogExceptionInfo(ctx);
		ReturnContext(ctx);
		return false;
	}

	ReturnContext(ctx);
	return true;
}

void Scripting::DiscardModule(const string & moduleName)
{
	scriptEngine->DiscardModule(moduleName.c_str());
}

void Scripting::Clear()
{
	for (auto ctx : ctxs)
		ctx->Release();

	ctxs.clear();
	ctxs.shrink_to_fit();
}

void Scripting::LogExceptionInfo(asIScriptContext * ctx)
{
	string execeptionDescription = ctx->GetExceptionString();
	const asIScriptFunction* function = ctx->GetExceptionFunction();

	string functionDeclaration = function->GetDeclaration();
	string moduleName = function->GetModuleName();
	string scriptPath = function->GetScriptSectionName();
	string scriptFile = FileSystem::GetFileNameFromPath(scriptPath);
	string exceptionLine = to_string(ctx->GetExceptionLineNumber());
}

void Scripting::Message_CallBack(const asSMessageInfo & msg)
{
	string fileName = FileSystem::GetFileNameFromPath(msg.section);
	string message = msg.message;

	string finalMessage;
	if (fileName != "")
		finalMessage = fileName + " " + message;
	else
		finalMessage = message;
}
