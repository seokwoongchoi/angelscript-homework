#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(Context * context)
	: ISubsystem(context)
{
	RegistResourceDirectory(ResourceType::Texture,		"../_Assets/Texture/");
	RegistResourceDirectory(ResourceType::Shader,		"../_Assets/Shader/");
	RegistResourceDirectory(ResourceType::Audio,		"../_Assets/Audio/");
	RegistResourceDirectory(ResourceType::Animation,	"../_Assets/Animation/");
	RegistResourceDirectory(ResourceType::Model,		"../_Assets/");
}

ResourceManager::~ResourceManager()
{
	for (auto resourceGroup : resourceGroups)
	{
		for (auto resource : resourceGroup.second)
			SAFE_DELETE(resource);
	}
	resourceGroups.clear();
	resourceDirectories.clear();
}

void ResourceManager::RegistResource(IResource * resource)
{
	assert(resource);
	resourceGroups[resource->GetResourceType()].push_back(resource);
}

void ResourceManager::RegistResourceDirectory(ResourceType type, const string & directory)
{
	resourceDirectories[type] = directory;
}
