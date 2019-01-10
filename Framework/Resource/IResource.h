#pragma once
#include "stdafx.h"

enum class ResourceType : uint
{
	Unknown,
	Texture,
	Shader,
	Animation,
	Audio,
	Model,
};

class IResource
{
public:
	template <typename T>
	static ResourceType DeduceResourceType();

public:
	IResource(class Context* context)
		: context(context)
	{
		resourceManager = context->GetSubsystem<class ResourceManager>();
	}
	virtual ~IResource() {}

	const string& GetResourceName() const { return name; }
	const string& GetResourcePath() const { return filePath; }
	const ResourceType& GetResourceType() const { return type; }

	void SetResourceName(const string& name) { this->name = name; }
	void SetResourcePath(const string& filePath) { this->filePath = filePath; }
	void SetResourceType(const ResourceType& type) { this->type = type; }
	
	virtual void SaveToFile(const string& saveFilePath)
	{

	}

	virtual void LoadFromFile(const string& loadFilePath)
	{

	}

protected:
	class Context* context;
	class ResourceManager* resourceManager;

	string name;
	string filePath;
	ResourceType type;
};

template<typename T>
inline ResourceType IResource::DeduceResourceType()
{
	string resourceType = typeid(T).name();

	ResourceType enumType = ResourceType::Unknown;

	if (resourceType.find("Texture") != string::npos)			enumType = ResourceType::Texture;
	else if (resourceType.find("Shader") != string::npos)		enumType = ResourceType::Shader;
	else if (resourceType.find("Animation") != string::npos)	enumType = ResourceType::Animation;
	else if (resourceType.find("Audio") != string::npos)		enumType = ResourceType::Audio;
	else if (resourceType.find("Model") != string::npos)		enumType = ResourceType::Model;

	return enumType;
}
