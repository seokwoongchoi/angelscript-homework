#include "stdafx.h"
#include "Widget_Inspector.h"
#include "../ImGui/Source/imgui_stdlib.h"
#include "../Utility/EditorHelper.h"
#include "../Utility/DragDrop.h"
#include "../../Framework/Scene/GameObject.h"
#include "../../Framework/Scene/Component/Transform.h"
#include "../../Framework/Scene/Component/Renderable.h"
#include "../../Framework/Scene/Component/Camera.h"
#include "../../Framework/Scene/Component/Script.h"


Widget_Inspector::Widget_Inspector()
{
}

Widget_Inspector::~Widget_Inspector()
{
}

void Widget_Inspector::Initialize(Context * context)
{
	IWidget::Initialize(context);
	title = "Inspector";
	
}

void Widget_Inspector::Render()
{
	if (EditorHelper::CurrentObject)
	{
		ShowTransform(EditorHelper::CurrentObject->GetComponent<Transform>());
		ShowCamera(EditorHelper::CurrentObject->GetComponent<Camera>());
		ShowScript(EditorHelper::CurrentObject->GetComponent<Script>());
	}
	ShowButton();

	auto data = DragDrop::GetDragDropPayload(DragDropPayloadType::Script);
	if (data.length())
	{
		if (auto script = EditorHelper::CurrentObject->AddComponent<Script>())
		{
			script->SetScript("../_Assets/Script/" + data);
		}
	}
	
}

void Widget_Inspector::ShowTransform(Transform * transform)
{
	if (!transform)
		return;

	Vector3 position = transform->GetPosition();
	Vector3 rotation = transform->GetRotate();
	Vector3 scale = transform->GetScale();

	auto ShowFloat = [](const char* label, float* value)
	{
		float step = 1.0f;
		float step_fast = 1.0f;
		char* decimals = "%.3f";
		auto flags = ImGuiInputTextFlags_CharsDecimal;

		ImGui::PushItemWidth(100.0f);
		ImGui::InputFloat(label, value, step, step_fast, decimals, flags);
		ImGui::PopItemWidth();
	};

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Position");
		ImGui::SameLine(70.0f); ShowFloat("##PositionX", &position.x);
		ImGui::SameLine();		ShowFloat("##PositionY", &position.y);
		ImGui::SameLine();		ShowFloat("##PositionZ", &position.z);

		ImGui::Text("Rotation");
		ImGui::SameLine(70.0f); ShowFloat("##RotationX", &rotation.x);
		ImGui::SameLine();		ShowFloat("##RotationY", &rotation.y);
		ImGui::SameLine();		ShowFloat("##RotationZ", &rotation.z);

		ImGui::Text("Scale");
		ImGui::SameLine(70.0f); ShowFloat("##ScaleX", &scale.x);
		ImGui::SameLine();		ShowFloat("##ScaleY", &scale.y);
		ImGui::SameLine();		ShowFloat("##ScaleZ", &scale.z);
	}

	transform->SetPosition(position);
	transform->SetRotate(rotation);
	transform->SetScale(scale);

	
}

void Widget_Inspector::ShowCamera(Camera * camera)
{
	if (!camera)
		return;

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
}

void Widget_Inspector::ShowScript(Script * script)
{
	if (!script)
		return;
	if (ImGui::CollapsingHeader("Script", ImGuiTreeNodeFlags_DefaultOpen))
	{
		string scriptName = script->GetName();

		ImGui::Text("Script");
		ImGui::SameLine();
		ImGui::PushItemWidth(100.0f);
		ImGui::InputText("##ScriptName", &scriptName, ImGuiInputTextFlags_ReadOnly);
		ImGui::PopItemWidth();
	}
}

void Widget_Inspector::ShowButton()
{
	ImGui::Separator();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f - 50.0f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
	if (ImGui::Button("Add Component"))
	{

	}
}

void Widget_Inspector::ShowMenuPopup()
{
}
