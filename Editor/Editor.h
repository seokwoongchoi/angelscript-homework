#pragma once

class Editor
{
public:
	static function<LRESULT(HWND, uint, WPARAM, LPARAM)> EditorProc;

public:
	Editor();
	virtual ~Editor();

	LRESULT MessageProc(HWND handle, uint message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void Initialize(class Context* context);
	void Render();

private:
	void ApplyStyle();
	void DockSpace();

private:
	class Context* context;
	vector<class IWidget*> widgets;
	bool bInitialized;
	bool bUsingDockSpace;
};