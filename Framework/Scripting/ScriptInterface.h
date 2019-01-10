#pragma once

class ScriptInterface
{
public:
	void Register(class Context* context, class asIScriptEngine* scriptEngine);

private:
	void RegisterEnumerations();
	void RegisterTypes();
	void RegisterSettings();
	void RegisterTimer();
	void RegisterInput();
	void RegisterGameObject();
	void RegisterTransform();
	void RegisterRenderable();
	void RegisterMaterial();
	void RegisterCamera();
	void RegisterMath();
	void RegisterVector2();
	void RegisterVector3();

private:
	class Context* context;
	class asIScriptEngine* scriptEngine;
};