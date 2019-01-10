#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "../Scene/Component/Transform.h"
#include "../Scene/Component/Camera.h"
#include "../Scene/Component/Script.h"

Scene::Scene(Context * context)
	: context(context)
	, mainCamera(nullptr)
	, name("")
	, bEditorMode(true)
	,bAdded(false)
	
{
	renderer=context->GetSubsystem<Renderer>();

	mainCamera = new GameObject(context);
	mainCamera->Initialize(mainCamera->AddComponent<Transform>());
	mainCamera->AddComponent<Camera>();
	
	/*auto script = mainCamera->AddComponent<Script>();
	script->SetScript("../_Assets/Script/FreeCamera.as");*/

	mainCamera->SetName("MainCamera");
	AddObject(mainCamera);

	//string test = "F:\\SGA\\Lecture\\1810_1600\\_Assets\\Icon\\AudioSourceGizmo.png";
	//string result = FileSystem::GetRelativeFilePath(test);
	//int a = 0;
}

Scene::~Scene()
{
	for (auto object : objects)
	{
		
		SAFE_DELETE(object);
	}
	objects.clear();
	objects.shrink_to_fit();
}

GameObject * Scene::CreateObject()
{
	auto object = new GameObject(context);
	object->Initialize(object->AddComponent<Transform>());
	AddObject(object);

	return object;
}

void Scene::AddObject(GameObject * object)
{
	objects.emplace_back(object);
	bAdded = true;
}

void Scene::RemoveObject(GameObject * object)
{
}

const bool Scene::IsExistObject(GameObject * object)
{
	return false;
}

void Scene::SaveSetting(bool & bSave)
{
	if (bSave)
	{
		for (auto object : objects)
		{
			object->Save();
			
		}
		bSave = false;
	}
}



void Scene::Update()
{
	bool bStarted = Engine::IsOnEngineFlags(EngineFlags_Game) && bEditorMode;
	bool bStopped = !Engine::IsOnEngineFlags(EngineFlags_Game) && !bEditorMode;
	bEditorMode = !Engine::IsOnEngineFlags(EngineFlags_Game);
	if (bAdded)
	{
		renderer->SetRenderables(this);
		bAdded = false;
	}
	if (bStarted)
	{
		for (auto object : objects)
			object->Start();
	}

	if (bStopped)
	{
		for (auto object : objects)
			object->Stop();
	}

	for (auto object : objects)
	{
		object->Update();
		
	}
	
		
	
		
}
