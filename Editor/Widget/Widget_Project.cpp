#include "stdafx.h"
#include "Widget_Project.h"
#include "../ImGui/Source/imgui_stdlib.h"
#include "../Utility/EditorHelper.h"
#include "../Utility/DragDrop.h"
#include "../Tool/Tool_Script.h"

void Widget_Project::Initialize(Context * context)
{
	IWidget::Initialize(context);

	title = "Project";
	selectItem = nullptr;
	bRenamePopup = false;
	UpdateItems();
}

void Widget_Project::Render()
{
	ShowFrame();

	if (ImGui::IsWindowHovered())
	{
		if (ImGui::GetIO().MouseDown[1])
			ImGui::OpenPopup("Project MenuPopup");
	}

	ShowPopup();
}

void Widget_Project::ShowFrame()
{
	for (auto& item : items)
	{
		if (ImGui::TreeNodeEx(item.label.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
		{
			if (ImGui::IsItemClicked(0) || ImGui::IsItemClicked(1))
				selectItem = &item;

			if (ImGui::IsItemHoveredRect())
			{
				if (ImGui::IsMouseDoubleClicked(0))
				{
					selectItem = &item;
					Tool_Script::Get().IsVisible() = true;
					Tool_Script::Get().SetScript("../_Assets/Script/" + selectItem->label);
				}
			}
			DragDrop::SetDragDropPayload(DragDropPayloadType::Script, item.label);
			ImGui::TreePop();
		}

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::SetCursorPosX(0.0f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7.0f);
		ImGui::ImageButton(item.thumbnail.texture->GetShaderResourceView(), ImVec2(14.0f, 14.0f));
		ImGui::PopStyleColor(2);
	}
}

void Widget_Project::ShowPopup()
{
	MenuPopup();
	RenamePopup();
}

void Widget_Project::MenuPopup()
{
	if (ImGui::BeginPopup("Project MenuPopup"))
	{
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Folder")) {}
			if (ImGui::MenuItem("Script"))
			{
				CreateScript();
				UpdateItems();
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Delete", nullptr, nullptr, selectItem != nullptr))
		{
			FileSystem::Delete_File("../_Assets/Script/" + selectItem->label);
			UpdateItems();
		}
		if (ImGui::MenuItem("Rename", nullptr, nullptr, selectItem != nullptr))
			bRenamePopup = true;

		ImGui::EndPopup();
	}
}

void Widget_Project::RenamePopup()
{
	if (bRenamePopup)
	{
		ImGui::OpenPopup("Project RenamePopup");
		bRenamePopup = false;
	}

	if (ImGui::BeginPopup("Project RenamePopup"))
	{
		if (!selectItem)
		{
			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
			return;
		}

		static bool bReset = false;
		static string to = FileSystem::GetIntactFileNameFromPath(selectItem->filePath);
		if (bReset)
		{
			to = FileSystem::GetIntactFileNameFromPath(selectItem->filePath);
			bReset = false;
		}

		ImGui::Text("Name : ");
		ImGui::InputText("##Rename", &to);

		if (ImGui::Button("Ok"))
		{
			RenameScript
			(
				FileSystem::GetIntactFileNameFromPath(selectItem->label),to
			);

			FileSystem::Delete_File("../_Assets/Script" + selectItem->label);
			UpdateItems();
			bReset = true;

			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
			return;
		}

		ImGui::EndPopup();
	}
}

void Widget_Project::CreateScript()
{
	static string baseScriptCode =
		"class NewScript\n\
 {\n\
 \tNewScript(GameObject @inObject)\n\
 \t{\n\
 \t}\n\
 \n\
 \tStart()\n\
 \t{\n\
 \t}\n\
 \n\
 \tUpdate()\n\
 \t{\n\
 \t}\n\
 }";

	ofstream out("../_Assets/Script/NewScript.as");
	{
		if (out.good())
		{
			out.write(baseScriptCode.c_str(), baseScriptCode.length());
		}
	}
}

void Widget_Project::UpdateItems()
{
	items.clear();
	items.shrink_to_fit();

	auto files = FileSystem::GetFilesInDirectory("../_Assets/Script/");
	for (const auto& file : files)
		items.emplace_back(file, IconProvider::Get().Load("", IconType::File));
}

void Widget_Project::RenameScript(const string & from, const string & to)
{
	ifstream in("../_Assets/Script/" + from + ".as");
	if (in.good())
	{
		string str((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		FileSystem::ReplaceAll(str, from, to);

		ofstream out("../_Assets/Script/" + to + ".as");
		if (out.good())
		{
			out.write(
				str.c_str(),
				str.length()
			);
		}
	}
}
