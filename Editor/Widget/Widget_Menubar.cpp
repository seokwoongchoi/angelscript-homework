#include "stdafx.h"
#include "Widget_Menubar.h"
#include "../Tool/Tool_Script.h"
#include "../Tool/Tool_Sprite.h"
#include "../Utility/EditorHelper.h"
#include "../../Framework/Scene/Scene.h"
#include "../../Framework/Scene/GameObject.h"
#include "../../Framework/Scene/Component/Transform.h"
#include "../../Framework/Scene/Component/Renderable.h"
void Widget_Menubar::Initialize(Context * context)
{
	sceneManager = context->GetSubsystem<SceneManager>();
	animation = new Animation(context);
}
void Widget_Menubar::Render()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load")) OpenFileDialog();

			ImGui::Separator();

			if (ImGui::MenuItem("Save")) { ConnectSceneforsave(); }
			if (ImGui::MenuItem("Save As..")) {}
				
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Metrics", nullptr, &bShowMetricsWindow);
			ImGui::MenuItem("Style", nullptr, &bShowStyleEditor);
			ImGui::MenuItem("Demo", nullptr, &bShowDemoWindow);
			ImGui::MenuItem("Script", nullptr, &Tool_Script::Get().IsVisible());
			ImGui::MenuItem("Sprite", nullptr, &Tool_Sprite::Get().IsVisible());
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (bShowMetricsWindow)				ImGui::ShowMetricsWindow();
	if (bShowStyleEditor)				ImGui::ShowStyleEditor();
	if (bShowDemoWindow)				ImGui::ShowDemoWindow();
	if (Tool_Script::Get().IsVisible()) Tool_Script::Get().Render();
	if (Tool_Sprite::Get().IsVisible()) Tool_Sprite::Get().Render();
}

void Widget_Menubar::ConnectSceneforsave()
{
	bSave = true;
	//sceneManager = context->GetSubsystem<SceneManager>();
	sceneManager->GetCurrentScene()->SaveSetting(bSave);
}



GameObject * Widget_Menubar::CreateEmpty()
{
	auto scene = sceneManager->GetCurrentScene();

	if (scene)
	{
		
			auto object = scene->CreateObject();
			return object;
	}

	return nullptr;
}

void Widget_Menubar::CreateQuad()
{
	animation->LoadFromFile("Save.xml");
	for (int i = 0; i < animation->GetKeyframeCount(); i++)
	{
		keyframes[i] = animation->GetKeyframeFromIndex(i);


		auto object = CreateEmpty();
		if (object)
		{

			auto renderable = object->AddComponent<Renderable>();
			renderable->SetModelType(ModelType::Quad);
			object->SetName("Quad");


			object->GetComponent<Transform>()->SetPosition(Vector3(keyframes[i].offset.x, keyframes[i].offset.y, 0.0f));
			object->GetComponent<Transform>()->SetScale(Vector3(keyframes[i].size.x, keyframes[i].size.y, 1.0f));

		}
	}
}

void Widget_Menubar::OpenFileDialog(string filePath)
{
	if (filePath.length() < 1)
	{
		/*FileSystem::OpenFileDialog
		(
			bind(&Widget_Menubar::OpenFileDialog, this, placeholders::_1),
			FileSystem::TextureFilter
		);*/
		
		FileSystem::OpenFileDialog
		(
			bind(&Widget_Menubar::OpenFileDialog, this, placeholders::_1),
			FileSystem::XmlFilter
		);
		if (FileSystem::XmlFilter)
		{
			CreateQuad();
		}
	}
	else
	{
		//TODO : 
	}
}

void Widget_Menubar::SaveFileDialog(string filePath)
{
	
	
}
