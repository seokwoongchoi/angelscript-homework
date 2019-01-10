#include "stdafx.h"
#include "Widget_Hierarchy.h"
#include "../Utility/EditorHelper.h"
#include "../../Framework/Scene/Scene.h"
#include "../../Framework/Scene/GameObject.h"
#include "../../Framework/Scene/Component/Transform.h"
#include "../../Framework/Scene/Component/Renderable.h"

Widget_Hierarchy::Widget_Hierarchy()
{
}

Widget_Hierarchy::~Widget_Hierarchy()
{
}

void Widget_Hierarchy::Initialize(Context * context)
{
	IWidget::Initialize(context);

	title = "Hierarchy";
	sceneManager = context->GetSubsystem<SceneManager>();
	
}

void Widget_Hierarchy::Render()
{
	ShowHierarchy();

	if (ImGui::IsWindowHovered())
	{
		if (ImGui::GetIO().MouseDown[1])
			ImGui::OpenPopup("Hierarchy MenuPopup");
	}

	ShowPopup();
}

void Widget_Hierarchy::ShowHierarchy()
{
	auto scenes = sceneManager->GetScenes();
	for (auto scene : scenes)
		AddScene(scene.second);
}

void Widget_Hierarchy::AddScene(Scene * scene)
{
	if (!scene)
		return;

	auto objects = scene->GetObjects();

	if (ImGui::CollapsingHeader(scene->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (auto object : objects)
		{
			AddObject(object);

			if (ImGui::IsItemClicked())
			{
				EditorHelper::CurrentObject = object;
			}
		}
	}
}

void Widget_Hierarchy::AddObject(GameObject * object)
{
	if (!object)
		return;

	if (ImGui::TreeNodeEx(object->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{

		ImGui::TreePop();
	}
}

void Widget_Hierarchy::ShowPopup()
{
	MenuPopup();
}

void Widget_Hierarchy::MenuPopup()
{
	if (ImGui::BeginPopup("Hierarchy MenuPopup"))
	{
		if (ImGui::MenuItem("Copy")) {}
		if (ImGui::MenuItem("Delete")) {}

		ImGui::Separator();

		if (ImGui::MenuItem("Empty Object")) CreateEmpty();

		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Quad")) CreateQuad();
			if (ImGui::MenuItem("Circle")) {}

			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

GameObject * Widget_Hierarchy::CreateEmpty()
{
	auto scene = sceneManager->GetCurrentScene();

	if (scene)
	{
		auto object = scene->CreateObject();
		return object;
	}

	return nullptr;
}

void Widget_Hierarchy::CreateQuad()
{
	auto object = CreateEmpty();
	
	
	
	if (object)
	{
		auto renderable = object->AddComponent<Renderable>();
		renderable->SetModelType(ModelType::Quad);
		object->SetName("Quad");

		object->GetComponent<Transform>()->SetScale(Vector3(50.0f, 50.0f, 1.0f));
		
	}
	
}

void Widget_Hierarchy::CreateScreenQuad()
{
}
