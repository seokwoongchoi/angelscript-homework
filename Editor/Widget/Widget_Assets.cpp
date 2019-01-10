#include "stdafx.h"
#include "Widget_Assets.h"
#include "../Utility/EditorHelper.h"
#include "../Utility/DragDrop.h"

Widget_Assets::Widget_Assets()
{
}

Widget_Assets::~Widget_Assets()
{
}

void Widget_Assets::Initialize(Context * context)
{
	IWidget::Initialize(context);
	title = "Assets";
	itemSize = 100.0f;
	itemSizeMin = 50.0f;
	itemSizeMax = 200.0f;
	currentPath = "../_Assets/Texture/";
	resourceManager = context->GetSubsystem<ResourceManager>();

	UpdateItems(currentPath);
}

void Widget_Assets::Render()
{
	if (ImGui::Button("Directory"))
	{
		//TODO : 
	}

	ImGui::SameLine();
	ImGui::Text(currentPath.c_str());
	ImGui::SameLine(ImGui::GetWindowContentRegionWidth() * 0.8f);
	ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.207f);
	ImGui::SliderFloat("##ItemSize", &itemSize, itemSizeMin, itemSizeMax);
	ImGui::PopItemWidth();

	ImGui::Separator();

	ShowItems();
}

void Widget_Assets::ShowItems()
{
	auto PushStyle = []()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 18.0f));
	};

	auto PopStyle = []() { ImGui::PopStyleVar(2); };

	ImVec2 contentSize = 
		ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();

	PushStyle();

	ImGui::BeginChild("##Child", contentSize, true);
	{
		int columns = static_cast<int>(ImGui::GetWindowContentRegionWidth() / itemSize);
		columns = columns < 1 ? 1 : columns;
		ImGui::Columns(columns, nullptr, false);
		for (auto& item : items)
		{
			//ImageButton
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			if (ImGui::ImageButton(item.thumbnail.texture->GetShaderResourceView(), ImVec2(itemSize, itemSize - 23.0f)))
			{
				//TODO :
			}
			ImGui::PopStyleColor(2);

			DragDrop::SetDragDropPayload(DragDropPayloadType::Texture, item.label);

			//Label
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - itemSize);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSize - 13.0f);
			ImGui::PushItemWidth(itemSize + 8.5f);
			{
				ImGui::TextWrapped(item.label.c_str());
			}
			ImGui::PopItemWidth();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemSize);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - itemSize + 13.0f);

			ImGui::NextColumn();
		}
	}
	ImGui::EndChild();

	PopStyle();
}

void Widget_Assets::UpdateItems(const string & path)
{
	if (!FileSystem::IsDirectory(path))
		return;

	items.clear();
	items.shrink_to_fit();

	vector<string> files;
	files = FileSystem::GetFilesInDirectory(path);
	for (const auto& file : files)
		items.emplace_back(file, IconProvider::Get().Load(file, IconType::Custom));
}
