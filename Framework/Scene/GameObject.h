#pragma once
#include "./Component/IComponent.h"

class GameObject
{
public:
	GameObject(class Context* context);
	virtual ~GameObject();

	void Initialize(class Transform* transform);

	void Start();
	void Update();
	void Stop();
	void Save();
	
	
	class Transform* GetTransform() const { return transform; }
	const string& GetName() const { return name; }
	const bool& IsActive() const { return bActive; }

	void SetName(const string& name) { this->name = name; }
	void SetIsActive(const bool& bActive) { this->bActive = bActive; }

	class IComponent* AddComponent(const ComponentType& type);
	template <typename T> T* AddComponent();
	template <typename T> T* GetComponent();
	template <typename T> vector<T*> GetComponents();
	
	const bool HasComponent(const ComponentType& type);

	template <typename T>
	const bool HasComponent()
	{
		return HasComponent(IComponent::DeduceComponentType<T>());
	}

	template <typename T>
	void RemoveComponent();

private:
	class Context* context;
	class Transform* transform;
	string name;
	bool bActive;
	
	vector<class IComponent*> components;
};

template<typename T>
inline T * GameObject::AddComponent()
{
	ComponentType type = IComponent::DeduceComponentType<T>();

	if (HasComponent(type) && type != ComponentType::Script)
		return GetComponent<T>();

	components.emplace_back
	(
		new T
		(
			context,
			this,
			transform
		)
	);

	auto newComponent = static_cast<T*>(components.back());
	newComponent->SetComponentType(type);
	newComponent->OnInitialize();

	return newComponent;
}

template<typename T>
inline T * GameObject::GetComponent()
{
	ComponentType type = IComponent::DeduceComponentType<T>();

	for (auto component : components)
	{
		if (component->GetComponentType() == type)
			return static_cast<T*>(component);
	}

	return nullptr;
}

template<typename T>
inline vector<T*> GameObject::GetComponents()
{
	ComponentType type = IComponent::DeduceComponentType<T>();

	vector<T*> tempComponents;
	for (auto component : components)
	{
		if (component->GetComponentType() != type)
			continue;

		tempComponents.emplace_back(static_cast<T*>(component));
	}

	return tempComponents;
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	ComponentType type = IComponent::DeduceComponentType<T>();

	for (auto iter = components.begin(); iter != components.end();)
	{
		auto component = *iter;
		if (type == component.second->GetComponentType())
		{
			component->OnDestroy();
			SAFE_DELETE(component.second);
			iter = components.erase(iter);
		}
		else
			iter++;
	}
}
