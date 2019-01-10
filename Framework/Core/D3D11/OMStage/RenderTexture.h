#pragma once

class RenderTexture
{
public:
	RenderTexture(class Context* context);
	virtual ~RenderTexture();

	ID3D11ShaderResourceView* GetShaderResource() const { return srv; }

	void Create
	(
		const uint& width,
		const uint& height,
		const DXGI_FORMAT& textureFormat = DXGI_FORMAT_R8G8B8A8_UNORM
	);
	void Clear(const D3DXCOLOR& color = D3DXCOLOR(0xff555566));
	void Clear(const float& r, const float& g, const float& b, const float& a = 1.0f);
	void SetRenderTarget();
	void Save(const string& filePath);

private:
	class Context* context;
	class Graphics* graphics;
	ID3D11Texture2D* rtvTexture;
	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;
	D3D11_VIEWPORT viewport;
};