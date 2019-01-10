#pragma once
#include "stdafx.h"
#include "../ImGui/Source/imgui.h"

class IWidget
{
public:
	virtual ~IWidget() {}

	virtual void Initialize(class Context* context)
	{
		this->context = context;
		title = "##";
		windowFlags = ImGuiWindowFlags_NoCollapse;
		bVisible = true;
	}

	virtual void Begin()
	{
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
		ImGui::Begin(title.c_str(), &bVisible, windowFlags);
	}

	virtual void End()
	{
		ImGui::End();
	}

	virtual void Render() = 0;

	const bool& IsVisible() const { return bVisible; }
	void SetIsVisible(const bool& bVisible) { this->bVisible = bVisible; }

	
protected:
	class Context* context;
	string title;
	int windowFlags;
	bool bVisible;
	
};