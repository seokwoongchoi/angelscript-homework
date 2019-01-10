#pragma once
#include "IWidget.h"

class Widget_Log : public IWidget
{
public:
	Widget_Log();
	virtual ~Widget_Log();

	void Initialize(class Context* context) override;
	void Render() override;

private:

};