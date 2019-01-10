#pragma once
#include "IWidget.h"

class Widget_Menubar : public IWidget
{
public:
	Widget_Menubar()
		: bShowMetricsWindow(false)
		, bShowStyleEditor(false)
		, bShowDemoWindow(false)
	{}
	virtual ~Widget_Menubar() {}
	void Initialize(class Context* context) override;
	

	void Begin() override {}
	void End() override {}
	void Render() override;
	void ConnectSceneforsave();
	
	class GameObject* CreateEmpty();
	void CreateQuad();
private:
	void OpenFileDialog(string filePath = "");
	void SaveFileDialog(string filePath = "");

private:
	bool bShowMetricsWindow;
	bool bShowStyleEditor;
	bool bShowDemoWindow;
	bool bSave;
	SceneManager* sceneManager;
	class ResourceManager* resourceManager;
	class Animation* animation;
	class Texture* texture;
	Keyframe keyframes[30];
};