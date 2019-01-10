#pragma once
#include "IResource.h"

class Texture : public IResource
{
public:
	Texture(class Context* context);
	virtual ~Texture();

	ID3D11ShaderResourceView* GetShaderResourceView() const { return srv; }
	const Vector2& GetSize() const { return size; }

	void CreateTextureFromFile(const string& filePath);
	void CreateTexture2D
	(
		const float& width,
		const float& height,
		const DXGI_FORMAT& format
	);
	void Clear();

	void BindPipeline(const ShaderType& type, const uint& slot);

	virtual void LoadFromFile(const string& loadFilePath) override;

private:
	class Graphics* graphics;
	ID3D11ShaderResourceView* srv;
	DXGI_FORMAT format;
	Vector2 size;
};