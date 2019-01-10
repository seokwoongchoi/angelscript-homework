#include "stdafx.h"
#include "Widget_ToolBar.h"
#include "../ImGui/Source/imgui_internal.h"
#include "../Utility/IconProvider.h"

float Widget_ToolBar::ToolBarHeight = 0.0f;

void Widget_ToolBar::Initialize(Context * contex)
{
	IWidget::Initialize(context);

	title = "ToolBar";
	windowFlags |=
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoTitleBar;
}

void Widget_ToolBar::Begin()
{
	ImGuiContext& ctx = *GImGui;
	float width = ctx.IO.DisplaySize.x;
	float height = ctx.FontBaseSize + ctx.Style.FramePadding.y * 2.0f - 1.0f;
	ToolBarHeight = height + 14.0f;

	ImGui::SetNextWindowPos(ImVec2(0.0f, height - 1.0f));
	ImGui::SetNextWindowSize(ImVec2(width, height + 16.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 4.0f));
	ImGui::Begin(title.c_str(), &bVisible, windowFlags);
}

void Widget_ToolBar::Render()
{
	ImGui::SameLine();
	ImGui::PushStyleColor
	(
		ImGuiCol_Button,
		ImGui::GetStyle().Colors[Engine::IsOnEngineFlags(EngineFlags_Game) ? ImGuiCol_ButtonActive : ImGuiCol_Button]
	);

	if (IconProvider::Get().ImageButton(IconType::Play, 20.0f))
		Engine::ToggleEngineFlags(EngineFlags_Game);

	ImGui::PopStyleColor();
}

void Widget_ToolBar::End()
{
	ImGui::PopStyleVar();
	ImGui::End();
}
