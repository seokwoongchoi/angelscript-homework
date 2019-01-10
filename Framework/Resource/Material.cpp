#include "stdafx.h"
#include "Material.h"

Material::Material(Context * context)
	: IResource(context)
	, shader(nullptr)
	, diffuseTexture(nullptr)
	, diffuseColor(0, 0, 0, 1)
{
}

Material::~Material()
{
}

void Material::SetShader(const string & filePath)
{
	shader = resourceManager->Load<Shader>(filePath);
}

void Material::SetDiffuseTexture(const string & filePath)
{
	diffuseTexture = resourceManager->Load<Texture>(filePath);
}

void Material::SaveToFile(const string & saveFilePath)
{
}

void Material::LoadFromFile(const string & loadFilePath)
{
}
