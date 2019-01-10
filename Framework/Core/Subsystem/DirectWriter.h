#pragma once
#include "ISubsystem.h"

struct Font
{
	wstring Name;
	float Size;
	DWRITE_FONT_WEIGHT Weight;
	DWRITE_FONT_STYLE Style;
	DWRITE_FONT_STRETCH Stretch;

	bool operator==(const Font& rhs)
	{
		bool bCheck = true;
		bCheck &= Name == rhs.Name;
		bCheck &= Size == rhs.Size;
		bCheck &= Weight == rhs.Weight;
		bCheck &= Style == rhs.Style;
		bCheck &= Stretch == rhs.Stretch;
		return bCheck;
	}
};

class DirectWriter : public ISubsystem
{
public:
	DirectWriter(class Context* context);
	virtual ~DirectWriter();

	const bool Initialize() override;

	void BeginTextDraw();
	void EndTextDraw();

	void Text
	(
		const wstring& text,
		const Vector2& position,
		const D3DXCOLOR& color = D3DXCOLOR(1, 1, 1, 1),
		const wstring& fontName = L"µ¸¿òÃ¼",
		const float& fontSize = 20.0f,
		const DWRITE_FONT_WEIGHT& fontWeight = DWRITE_FONT_WEIGHT_NORMAL,
		const DWRITE_FONT_STYLE& fontStyle = DWRITE_FONT_STYLE_NORMAL,
		const DWRITE_FONT_STRETCH& fontStretch = DWRITE_FONT_STRETCH_NORMAL
	);

private:
	ID2D1SolidColorBrush* RegistBrush(const D3DXCOLOR& color);
	IDWriteTextFormat* RegistFormat
	(
		const wstring& fontName,
		const float& fontSize,
		const DWRITE_FONT_WEIGHT& fontWeight,
		const DWRITE_FONT_STYLE& fontStyle,
		const DWRITE_FONT_STRETCH& fontStretch
	);

	ID2D1SolidColorBrush* FindBrush(const D3DXCOLOR& color);
	IDWriteTextFormat* FindFormat(const Font& font);

private:
	IDWriteFactory* writeFactory;
	ID2D1Factory1* factory;
	ID2D1Device* writeDevice;
	ID2D1DeviceContext* writeDeviceContext;
	ID2D1Bitmap1* targetBitmap;

	vector<pair<D3DXCOLOR, ID2D1SolidColorBrush*>> brushes;
	vector<pair<Font, IDWriteTextFormat*>> formats;
};