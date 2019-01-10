#pragma once
#include "stdafx.h"
#include "../ImGui/Source/imgui.h"

enum class DragDropPayloadType : uint
{
	Unknown,
	Texture,
	Object,
	Model,
	Audio,
	Script,
};

class DragDrop
{
public:
	static void SetDragDropPayload(const DragDropPayloadType& type, const string& data)
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			ImGui::SetDragDropPayload
			(
				reinterpret_cast<const char*>(&type),
				data.c_str(),
				data.length() + 1
			);
			ImGui::Text(data.c_str());
			ImGui::EndDragDropSource();
		}
	}

	static const string GetDragDropPayload(const DragDropPayloadType& type)
	{
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload
			(
				reinterpret_cast<const char*>(&type)
			);

			if (payload)
				return reinterpret_cast<const char*>(payload->Data);

			ImGui::EndDragDropTarget();
		}

		return "";
	}
};