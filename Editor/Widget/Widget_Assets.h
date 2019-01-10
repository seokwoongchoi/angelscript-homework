#pragma once
#include "IWidget.h"

class Widget_Assets : public IWidget
{
public:
	Widget_Assets();
	virtual ~Widget_Assets();

	void Initialize(class Context* context) override;
	void Render() override;

private:
	void ShowItems();

private:
	void UpdateItems(const string& path);

private:
	class ResourceManager* resourceManager;

	string currentPath;
	float itemSize;
	float itemSizeMin;
	float itemSizeMax;
	vector<struct Item> items;
};