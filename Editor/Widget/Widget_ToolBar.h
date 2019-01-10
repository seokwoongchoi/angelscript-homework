#pragma once
#include "IWidget.h"

class Widget_ToolBar : public IWidget
{
public:
	Widget_ToolBar() {}
	virtual ~Widget_ToolBar() {}

	void Initialize(class Context* contex) override;
	void Begin() override;
	void Render() override;
	void End() override;

public:
	static float ToolBarHeight;
};