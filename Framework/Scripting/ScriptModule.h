#pragma once

class ScriptModule
{
public:
	ScriptModule(class Scripting* scriptEngine, const string& moduleName);
	virtual ~ScriptModule();

	const bool LoadScript(const string& filePath);
	class asIScriptModule* GetAsIScriptModule();

private:
	class CScriptBuilder* builder;
	class Scripting* scriptEngine;
	string moduleName;
};