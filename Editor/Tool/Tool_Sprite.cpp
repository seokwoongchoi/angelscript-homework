#include "stdafx.h"
#include "Tool_Sprite.h"
#include "../ImGui/Source/imgui.h"
#include "../Utility/DragDrop.h"
#include "../Utility/EditorHelper.h"

void Tool_Sprite::Initialize(Context * context)
{
	this->context = context;
	this->resourceManager = context->GetSubsystem<ResourceManager>();
	this->texture = nullptr;
	this->gridSpacing = 10.0f;
	this->gridColor = D3DXCOLOR(0, 1, 0, 1);
	this->bVisible = false;
}

void Tool_Sprite::Render()
{
	if (!bVisible)
		return;

	ImGui::Begin("SpriteTool", &bVisible);
	{
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		ImVec2 size = ImGui::GetWindowSize();
		ShowSpriteFrame(size);
		DragDrop();
		ShowSpriteInfo(size);
		ShowSpriteEdit(size);
	}
	ImGui::End();
}

void Tool_Sprite::ShowSpriteFrame(const ImVec2 & size)
{
	ImGui::BeginChild("##SpriteFrame", ImVec2(size.x * 0.5f, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	{
		if (texture)
		{
			ImVec2 windowPos = ImGui::GetCursorPos() + ImGui::GetWindowPos();
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			//Vertical
			for (float x = 0; x <= texture->GetSize().x; x += gridSpacing)
				drawList->AddLine
				(
					ImVec2(x + windowPos.x, windowPos.y),
					ImVec2(x + windowPos.x, windowPos.y + texture->GetSize().y),
					gridColor
				);

			//Horizontal
			for (float y = 0; y <= texture->GetSize().y; y += gridSpacing)
				drawList->AddLine
				(
					ImVec2(windowPos.x, y + windowPos.y),
					ImVec2(windowPos.x + texture->GetSize().x, y + windowPos.y),
					gridColor
				);
		
			ImGui::Image
			(
				texture->GetShaderResourceView(),
				EditorHelper::ToImVec2(texture->GetSize())
			);
		}
	}
	ImGui::EndChild();
}

void Tool_Sprite::ShowSpriteInfo(const ImVec2 & size)
{
	ImGui::SameLine();
	ImGui::BeginChild("##SpriteInfo", ImVec2(size.x * 0.25f - 20.0f, 0), true);
	{

	}
	ImGui::EndChild();
}

void Tool_Sprite::ShowSpriteEdit(const ImVec2 & size)
{
	ImGui::SameLine();
	ImGui::BeginChild("##SpriteEdit", ImVec2(size.x * 0.25f - 10.0f, 0), true);
	{

	}
	ImGui::EndChild();
}

void Tool_Sprite::DragDrop()
{
	auto data = DragDrop::GetDragDropPayload(DragDropPayloadType::Texture);
	if (data.length())
		texture = resourceManager->Load<Texture>(data);
}
