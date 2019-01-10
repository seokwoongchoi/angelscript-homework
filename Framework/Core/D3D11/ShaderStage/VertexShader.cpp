#include "stdafx.h"
#include "VertexShader.h"

VertexShader::VertexShader(Context * context)
	: BaseShader(context)
	, vertexShader(nullptr)
	, vsBlob(nullptr)
{
}

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(const string & filePath, const string & functionName)
{
	this->shaderFilePath = filePath;
	this->functionName = functionName;

	ID3D10Blob* error = nullptr;
	HRESULT hr = D3DX11CompileFromFileA
	(
		shaderFilePath.c_str(),
		nullptr,
		nullptr,
		functionName.c_str(),
		"vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS, //���Ĺ����� ������ üũ�ؼ� ������Ŵ
		0,
		nullptr,
		&vsBlob,
		&error,
		nullptr
	);
	assert(CheckShaderError(hr, error));

	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(error);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(vsBlob);
}

void VertexShader::BindPipeline()
{
	graphics->GetDeviceContext()->VSSetShader(vertexShader, nullptr, 0);
}
