#pragma once

class VertexBuffer
{
public:
	VertexBuffer(class Context* context);
	virtual ~VertexBuffer();

	template <typename T>
	void Create
	(
		const vector<T>& vertices, 
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT
	);
	void Clear();

	void* Map();
	void Unmap();

	void BindPipeline();

private:
	class Graphics* graphics;

	ID3D11Buffer* vbuffer;
	uint stride;
	uint offset;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE & usage)
{
	assert(!vertices.empty());

	Clear();

	stride = sizeof(T);

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;

	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(T) * vertices.size();

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();

	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&vbuffer
	);
	assert(SUCCEEDED(hr));
}
