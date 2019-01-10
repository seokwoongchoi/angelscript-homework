#pragma once

class Pipeline
{
public:
	Pipeline(class Context* context);
	virtual ~Pipeline();

	void SetInputLayout(class InputLayout* inputLayout);
	void SetVertexBuffer(class VertexBuffer* vertexBuffer);
	void SetIndexBuffer(class IndexBuffer* indexBuffer);
	void SetPrimitiveTopology(class PrimitiveTopology* primitiveTopology);
	void SetVertexShader(class VertexShader* vertexShader);
	void SetPixelShader(class PixelShader* pixelShadser);

	void SetConstantBuffer(class ConstantBuffer* cbuffer);
	void SetTexture(const ShaderType& type, class Texture* texture);

	void BindPipeline();

private:
	class Graphics* graphics;

	class InputLayout* inputLayout;
	class VertexBuffer* vertexBuffer;
	class IndexBuffer* indexBuffer;
	class PrimitiveTopology* primitiveTopology;
	class VertexShader* vertexShader;
	class PixelShader* pixelShadser;

	vector<class ConstantBuffer*> constantBuffers;
	map<ShaderType, vector<ID3D11ShaderResourceView*>> textures;

	bool bInputLayout;
	bool bVertexBuffer;
	bool bIndexBuffer;
	bool bPrimitiveTopology;
	bool bVertexShader;
	bool bPixelShader;
};