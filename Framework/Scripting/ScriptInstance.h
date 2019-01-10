#pragma once

class ScriptInstance
{
public:
	ScriptInstance();
	virtual ~ScriptInstance();

	const bool Instantiate
	(
		const string& path,
		class GameObject* object,
		class Scripting* scriptEngine
	);
	const bool& IsInstantiated() const { return bInstantiated; }
	const string& GetScriptPath() const { return scriptPath; }

	void ExcuteStart();
	void ExcuteUpdate();

private:
	const bool CreateScriptObject();

private:
	class Scripting* scriptEngine;
	class asIScriptObject* scriptObject;
	class asIScriptFunction* startFunction;
	class asIScriptFunction* updateFunction;
	class asIScriptFunction* constructorFunction;
	class ScriptModule* scriptModule;
	class GameObject* object;
	string scriptPath;
	string className;
	string constructorDeclaration;
	string moduleName;
	bool bInstantiated;
};