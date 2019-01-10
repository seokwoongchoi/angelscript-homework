#pragma once

class Tool_Sprite
{
public:
	static Tool_Sprite& Get()
	{
		static Tool_Sprite instance;
		return instance;
	}

	void Initialize(class Context* context);
	void Render();

	bool& IsVisible() { return bVisible; }

private:
	Tool_Sprite() {}
	virtual ~Tool_Sprite() {}

	void ShowSpriteFrame(const struct ImVec2& size);
	void ShowSpriteInfo(const struct ImVec2& size);
	void ShowSpriteEdit(const struct ImVec2& size);

	void DragDrop();

private:
	class Context* context;
	class ResourceManager* resourceManager;
	class Texture* texture;

	float gridSpacing;
	D3DXCOLOR gridColor;
	bool bVisible;
};