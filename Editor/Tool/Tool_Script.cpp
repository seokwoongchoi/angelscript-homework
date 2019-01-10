#include "stdafx.h"
#include "Tool_Script.h"

void Tool_Script::Initialize(Context * context)
{
	this->context = context;
	filePath = "";
	bVisible = false;

	auto language = TextEditor::LanguageDefinition::AngelScript();
	{
	}
	textEditor.SetLanguageDefinition(language);
}

void Tool_Script::Render()
{
	if (!bVisible)
		return;

	auto cursorPos = textEditor.GetCursorPosition();

	ImGui::Begin("ScriptTool", &bVisible, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
	{
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					auto text = textEditor.GetText();
					auto scriptname = this->filePath;
					ofstream out(scriptname);
					{
						if (out.good())
						{
							out.write(text.c_str(), text.length());
						}
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				bool bReadOnly = textEditor.IsReadOnly();
				if (ImGui::MenuItem("ReadOnly Mode", nullptr, &bReadOnly))
					textEditor.SetReadOnly(bReadOnly);

				ImGui::Separator();

				if (ImGui::MenuItem("Undo", "Alt + <-", nullptr, !bReadOnly && textEditor.CanUndo()))
					textEditor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl + Y", nullptr, !bReadOnly && textEditor.CanRedo()))
					textEditor.Redo();

				ImGui::Separator();

				if (ImGui::MenuItem("Copy", "Ctrl + C", nullptr, textEditor.HasSelection()))
					textEditor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl + X", nullptr, !bReadOnly && textEditor.HasSelection()))
					textEditor.Cut();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !bReadOnly && textEditor.HasSelection()))
					textEditor.Delete();
				if (ImGui::MenuItem("Paste", "Ctrl + V", nullptr, !bReadOnly && ImGui::GetClipboardText() != nullptr))
					textEditor.Paste();

				ImGui::Separator();

				if (ImGui::MenuItem("Select All", "Ctrl + A", nullptr))
					textEditor.SelectAll();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark"))
					textEditor.SetPalette(TextEditor::GetDarkPalette());
				if (ImGui::MenuItem("Light"))
					textEditor.SetPalette(TextEditor::GetLightPalette());
				if (ImGui::MenuItem("Retro Blue"))
					textEditor.SetPalette(TextEditor::GetRetroBluePalette());

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Text
		(
			"%6d/%-6d %6d lines | %s | %s | %s | %s",
			cursorPos.mLine + 1,
			cursorPos.mColumn + 1,
			textEditor.GetTotalLines(),
			textEditor.IsOverwrite() ? "Ovr" : "Ins",
			textEditor.CanUndo() ? "*" : " ",
			textEditor.GetLanguageDefinition().mName.c_str(),
			filePath.c_str()
		);

		textEditor.Render("ScriptTool");
	}
	ImGui::End();

}

void Tool_Script::SetScript(const string & filePath)
{
	this->filePath = filePath;

	ifstream in(filePath); 
	if (in.good())
	{
		string str((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		textEditor.SetText(str);
	}

}

Tool_Script::Tool_Script()
{
}

Tool_Script::~Tool_Script()
{
}
