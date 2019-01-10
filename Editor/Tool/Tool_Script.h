#pragma once
#include "../ImGui/TextEditor.h"

class Tool_Script
{
public:
	static Tool_Script& Get()
	{
		static Tool_Script instance;
		return instance;
	}

	void Initialize(class Context* context);
	void Render();

	void SetScript(const string& filePath);

	bool& IsVisible() { return bVisible; }

private:
	Tool_Script();
	virtual ~Tool_Script();

private:
	class Context* context;

	TextEditor textEditor;
	TextEditor::ErrorMarkers markers;

	string filePath;
	bool bVisible;
};