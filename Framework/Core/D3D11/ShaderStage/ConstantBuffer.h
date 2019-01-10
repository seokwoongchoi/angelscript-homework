#pragma once

class ConstantBuffer
{
public:
	ConstantBuffer(class Context* context);
	virtual ~ConstantBuffer();

	template <typename T>
	void Create
	(
		const ShaderType& shaderType, 
		const uint& slot, 
		const D3D11_USAGE& usage = D3D11_USAGE_DYNAMIC
	);
	void Clear();

	void* Map();
	void Unmap();

	void BindPipeline();

private:
	class Graphics* graphics;
	ID3D11Buffer* cbuffer;
	ShaderType shaderType;
	uint slot;
};

template<typename T>
inline void ConstantBuffer::Create(const ShaderType & shaderType, const uint & slot, const D3D11_USAGE & usage)
{
	this->shaderType = shaderType;
	this->slot = slot;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;

	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = sizeof(T);

	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		nullptr,
		&cbuffer
	);
	assert(SUCCEEDED(hr));
}
