#include "stdafx.h"
#include "Animation.h"

Animation::Animation(Context * context)
	: IResource(context)
	, repeatType(AnimationRepeatType::Once)
{
	keyframes.clear();
}

Animation::~Animation()
{
}

const Keyframe & Animation::GetKeyframeFromIndex(const uint & index)
{
	assert(index < keyframes.size());
	return keyframes[index];
}

void Animation::AddKeyframe(const Keyframe & keyframe)
{
	keyframes.push_back(keyframe);
}

void Animation::SaveToFile(const string & saveFilePath)
{
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);

	Xml::XMLElement* root = doc.NewElement("SpriteAnimation");
	doc.LinkEndChild(root);

	root->SetAttribute("AnimationName", name.c_str());
	root->SetAttribute("RepeatType", static_cast<uint>(repeatType));

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* firstElem = doc.NewElement("Keyframe");
		root->LinkEndChild(firstElem);

		firstElem->SetAttribute("TexturePath", keyframe.texture->GetResourcePath().c_str());
		firstElem->SetAttribute("OffsetX", keyframe.offset.x);
		firstElem->SetAttribute("OffsetY", keyframe.offset.y);
		firstElem->SetAttribute("SizeX", keyframe.size.x);
		firstElem->SetAttribute("SizeY", keyframe.size.y);
		firstElem->SetAttribute("Time", keyframe.time);
	}
	doc.SaveFile(saveFilePath.c_str());
}

void Animation::LoadFromFile(const string & loadFilePath)
{
	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(loadFilePath.c_str());
	assert(error == Xml::XMLError::XML_SUCCESS);

	Xml::XMLElement* root = doc.FirstChildElement();
	name = root->Attribute("AnimationName");
	repeatType = static_cast<AnimationRepeatType>(root->IntAttribute("RepeatType"));

	Xml::XMLElement* firstElem = root->FirstChildElement();
	for (; firstElem != nullptr; firstElem = firstElem->NextSiblingElement())
	{
		Keyframe keyframe;
		string texturePath = firstElem->Attribute("TexturePath");

		keyframe.texture = resourceManager->Load<Texture>("tree.png");
		keyframe.offset.x = firstElem->FloatAttribute("OffsetX");
		keyframe.offset.y = firstElem->FloatAttribute("OffsetY");
		keyframe.size.x = firstElem->FloatAttribute("SizeX");
		keyframe.size.y = firstElem->FloatAttribute("SizeY");
		keyframe.time = firstElem->FloatAttribute("Time");

		keyframes.push_back(keyframe);
	}
}
