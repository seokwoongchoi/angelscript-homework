#pragma once
#include "ISubsystem.h"
#include "../../Resource/IResource.h"

class ResourceManager : public ISubsystem
{
public:
	ResourceManager(class Context* context);
	virtual ~ResourceManager();

	template <typename T> T* Load(const string& path);
	template <typename T> T* GetResourceFromName(const string& name);
	template <typename T> T* GetResourceFromPath(const string& path);

	void RegistResource(class IResource* resource);
	void RegistResourceDirectory(ResourceType type, const string& directory);

	const bool Initialize() override { return true; }

private:
	typedef vector<class IResource*> ResourceGroup;
	map<ResourceType, ResourceGroup> resourceGroups;
	map<ResourceType, string> resourceDirectories;
};

template<typename T>
inline T * ResourceManager::Load(const string & path)
{
	auto resource = GetResourceFromPath<T>(path);

	if (!resource)
	{
		auto type = IResource::DeduceResourceType<T>();
		auto directory = resourceDirectories[type];

		resource = new T(context);
		resource->SetResourceType(type);
		resource->SetResourcePath(path);
		resource->SetResourceName(FileSystem::GetIntactFileNameFromPath(path));
		resource->LoadFromFile(directory + path);

		RegistResource(resource);
	}

	return resource;
}

template<typename T>
inline T * ResourceManager::GetResourceFromName(const string & name)
{
	for (auto resource : resourceGroups[IResource::DeduceResourceType<T>()])
	{
		if (resource->GetResourceName() == name)
			return static_cast<T*>(resource);
	}
	return nullptr;
}

template<typename T>
inline T * ResourceManager::GetResourceFromPath(const string & path)
{
	for (auto resource : resourceGroups[IResource::DeduceResourceType<T>()])
	{
		if (resource->GetResourcePath() == path)
			return static_cast<T*>(resource);
	}
	return nullptr;
}
