#pragma once
#include "IWidget.h"

class Widget_Hierarchy : public IWidget
{
public:
	Widget_Hierarchy();
	virtual ~Widget_Hierarchy();

	void Initialize(class Context* context) override;
	void Render() override;

	
private:
	void ShowHierarchy();
	void AddScene(class Scene* scene);
	void AddObject(class GameObject* object);

private:
	void ShowPopup();
	void MenuPopup();

private:
	class GameObject* CreateEmpty();
	void CreateQuad();
	void CreateScreenQuad();

private:
	class SceneManager* sceneManager;
	
};