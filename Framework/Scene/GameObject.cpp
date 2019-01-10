#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(Context * context)
	: context(context)
	, transform(nullptr)
	, name("")
	, bActive(true)
{
}

GameObject::~GameObject()
{
	for (auto iter = components.begin(); iter != components.end();)
	{
		(*iter)->OnDestroy();
		SAFE_DELETE(*iter);

		iter = components.erase(iter);
	}
	components.clear();
}

void GameObject::Initialize(Transform * transform)
{
	this->transform = transform;
}

void GameObject::Start()
{
	for (auto component : components)
		component->OnStart();
}

void GameObject::Update()
{
	if (!bActive)
		return;

	for (auto component : components)
		component->OnUpdate();
}

void GameObject::Stop()
{
	for (auto component : components)
		component->OnStop();
}

void GameObject::Save()
{
	for (auto component : components)
		component->OnSave();
}




IComponent * GameObject::AddComponent(const ComponentType & type)
{
	IComponent* component = nullptr;

	switch (type)
	{
	case ComponentType::Camera: break;
	case ComponentType::Renderable: break;
	case ComponentType::Transform: break;
	case ComponentType::Animator: break;
	case ComponentType::AudioSource: break;
	case ComponentType::AudioListener: break;
	case ComponentType::Collider: break;
	case ComponentType::LineRenderer: break;
	case ComponentType::Light: break;
	}

	return component;
}

const bool GameObject::HasComponent(const ComponentType & type)
{
	for (auto component : components)
	{
		if (component->GetComponentType() == type)
			return true;
	}
	return false;
}
