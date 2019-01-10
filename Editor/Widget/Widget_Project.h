#pragma once
#include "IWidget.h"

class Widget_Project : public IWidget
{
public:
	Widget_Project() {}
	virtual ~Widget_Project() {}

	void Initialize(class Context* context) override;
	void Render() override;

private:
	void ShowFrame();
	void ShowPopup();

private:
	void MenuPopup();
	void RenamePopup();
	
private:
	void CreateScript();

private:
	void UpdateItems();
	void RenameScript(const string& from, const string& to);

private:
	struct Item* selectItem;
	bool bRenamePopup;
	vector<struct Item> items;
};