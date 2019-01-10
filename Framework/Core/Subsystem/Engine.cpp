#include "stdafx.h"
#include "Engine.h"
#include "../../Scene/Scene.h"

unsigned long Engine::engineFlags = 0UL;

Engine::Engine(Context * context)
	: ISubsystem(context)
	, timer(nullptr)
	, input(nullptr)
	, sceneManager(nullptr)
	, renderer(nullptr)
{
	engineFlags =
		EngineFlags_Update |
		EngineFlags_Render;

	//context 생성과 서브시스템 등록
	context->RegistSubsystem(this);
	context->RegistSubsystem(new Timer(context));
	context->RegistSubsystem(new Input(context));
	context->RegistSubsystem(new Graphics(context));
	context->RegistSubsystem(new DirectWriter(context));
	context->RegistSubsystem(new ResourceManager(context));
	context->RegistSubsystem(new Audio(context));
	context->RegistSubsystem(new ColliderManager(context));
	context->RegistSubsystem(new Renderer(context));
	context->RegistSubsystem(new Scripting(context));
	context->RegistSubsystem(new SceneManager(context));
}

Engine::~Engine()
{
}

const bool Engine::Initialize()
{
	//Timer
	timer = context->GetSubsystem<Timer>();
	if (!timer->Initialize())
	{
		//TODO :
	}

	//Input
	input = context->GetSubsystem<Input>();
	if (!input->Initialize())
	{

	}

	//Graphics
	if (!context->GetSubsystem<Graphics>()->Initialize())
	{

	}

	//DirectWriter
	if (!context->GetSubsystem<DirectWriter>()->Initialize())
	{

	}

	//ResourceManager
	if (!context->GetSubsystem<ResourceManager>()->Initialize())
	{

	}

	//Audio
	if (!context->GetSubsystem<Audio>()->Initialize())
	{

	}

	//ColliderManager
	if (!context->GetSubsystem<ColliderManager>()->Initialize())
	{

	}

	//Renderer
	renderer = context->GetSubsystem<Renderer>();
	if (!renderer->Initialize())
	{

	}

	//Scripting
	if (!context->GetSubsystem<Scripting>()->Initialize())
	{

	}

	//SceneManager
	sceneManager = context->GetSubsystem<SceneManager>();
	if (!sceneManager->Initialize())
	{

	}

	sceneManager->RegistScene("First", new Scene(context));
	sceneManager->SetCurrentScene("First");

	return true;
}

void Engine::Update()
{
	timer->Update();
	input->Update();

	if (IsOnEngineFlags(EngineFlags_Update))
		sceneManager->Update();

	if (IsOnEngineFlags(EngineFlags_Render))
		renderer->Render();
}
