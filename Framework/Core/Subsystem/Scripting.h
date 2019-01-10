#pragma once
#include "ISubsystem.h"

class Scripting : public ISubsystem
{
public:
	Scripting(class Context* context);
	virtual ~Scripting();

	const bool Initialize() override;

	//Script Engine
	class asIScriptEngine* GetAsIScriptEngine();

	//Context
	class asIScriptContext* RequestContext();
	void ReturnContext(class asIScriptContext* ctx);

	//Calls
	const bool ExecuteCall
	(
		class asIScriptFunction* scriptFunc,
		class asIScriptObject* obj
	);

	//Module
	void DiscardModule(const string& moduleName);

	void Clear();

private:
	void LogExceptionInfo(class asIScriptContext* ctx);
	void Message_CallBack(const struct asSMessageInfo& msg);

private:
	class asIScriptEngine* scriptEngine;
	vector<class asIScriptContext*> ctxs;
};