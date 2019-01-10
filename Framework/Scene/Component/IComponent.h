#pragma once
#include "stdafx.h"

enum class ComponentType : uint
{
	Unknown,
	Camera,
	Renderable,
	Transform,
	Animator,
	AudioSource,
	AudioListener,
	Collider,
	LineRenderer,
	Light,
	Script,
	SaveObject,
};

class IComponent
{
public:
	template <typename T>
	static const ComponentType DeduceComponentType();

public:
	IComponent
	(
		class Context* context,
		class GameObject* object,
		class Transform* transform
	)
		: context(context)
		, object(object)
		, transform(transform)
		, bEnabled(true)
	{}
	virtual ~IComponent() {}

	virtual void OnInitialize() = 0;
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnStop() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnSave() = 0;


	class GameObject* GetGameObject() const { return object; }
	class Transform* GetTransform() const { return transform; }
	const ComponentType& GetComponentType() const { return componentType; }
	const bool& IsEnabled() const { return bEnabled; }

	void SetComponentType(const ComponentType& componentType) { this->componentType = componentType; }
	void SetIsEnabled(const bool& bEnabled) { this->bEnabled = bEnabled; }

	
protected:
	class Context* context;
	class GameObject* object;
	class Transform* transform;
	ComponentType componentType;


	
	
	bool bEnabled;
};

template<typename T>
inline const ComponentType IComponent::DeduceComponentType()
{
	string type = typeid(T).name();

	ComponentType enumType = ComponentType::Unknown;

	if (type.find("Camera") != string::npos)			enumType = ComponentType::Camera;
	else if (type.find("Renderable") != string::npos)	enumType = ComponentType::Renderable;
	else if (type.find("Transform") != string::npos)	enumType = ComponentType::Transform;
	else if (type.find("Animator") != string::npos)		enumType = ComponentType::Animator;
	else if (type.find("AudioSource") != string::npos)	enumType = ComponentType::AudioSource;
	else if (type.find("AudioListener") != string::npos)enumType = ComponentType::AudioListener;
	else if (type.find("Collider") != string::npos)		enumType = ComponentType::Collider;
	else if (type.find("LineRenderer") != string::npos)	enumType = ComponentType::LineRenderer;
	else if (type.find("Light") != string::npos)		enumType = ComponentType::Light;
	else if (type.find("Script") != string::npos)		enumType = ComponentType::Script;
	else if (type.find("SaveObject") != string::npos)	enumType = ComponentType::SaveObject;

	return enumType;
}
