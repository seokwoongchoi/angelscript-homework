#include "stdafx.h"
#include "SceneManager.h"
#include "../../Scene/Scene.h"

SceneManager::SceneManager(Context * context)
	: ISubsystem(context)
	, currentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	//1
	//map<string, Scene*>::iterator iter = sceneTable.begin();
	//for (; iter != sceneTable.end(); iter++)
	//	SAFE_DELETE(iter->second);

	//2
	for (auto scene : scenes)
		SAFE_DELETE(scene.second);
}

void SceneManager::SetCurrentScene(const string & sceneName)
{
	assert(scenes.count(sceneName) > 0);
	currentScene = scenes[sceneName];
}

void SceneManager::RegistScene(const string & sceneName, Scene * scene)
{
	assert(scenes.count(sceneName) < 1);
	scene->SetName(sceneName);
	scenes[sceneName] = scene;
}

void SceneManager::Update()
{
	if (currentScene)
		currentScene->Update();
}