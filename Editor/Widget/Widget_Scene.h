#pragma once
#include "IWidget.h"

class Widget_Scene : public IWidget
{
public:
	Widget_Scene();
	virtual ~Widget_Scene();

	void Initialize(class Context* context) override;
	void Render() override;

private:
	void ShowFrame();
	void ShowGizmo();

private:
	void Picking();
	void DragDrop();
	

private:
	class SceneManager* sceneManager;
	class Renderer* renderer;

	class Camera* camera;
	Vector2 framePos;
	Vector2 frameSize;

	class ResourceManager* resourceManager;
	class Animation* animation;
	class Texture* texture;
	
};