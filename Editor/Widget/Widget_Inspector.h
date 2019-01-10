#pragma once
#include "IWidget.h"

class Widget_Inspector : public IWidget
{
public:
	Widget_Inspector();
	virtual ~Widget_Inspector();

	void Initialize(class Context* context) override;
	void Render() override;
private:
	void ShowTransform(class Transform* transform);
	void ShowCamera(class Camera* camera);
	void ShowScript(class Script* script);
private:
	void ShowButton();
	void ShowMenuPopup();


	
};