#include "stdafx.h"
#include "PixelShader.h"

PixelShader::PixelShader(Context * context)
	: BaseShader(context)
	, pixelShader(nullptr)
{
}

PixelShader::~PixelShader()
{
	Clear();
}

void PixelShader::Create(const string & filePath, const string & functionName)
{
	this->shaderFilePath = filePath;
	this->functionName = functionName;

	ID3D10Blob* error = nullptr, *psBlob = nullptr;
	HRESULT hr = D3DX11CompileFromFileA
	(
		shaderFilePath.c_str(),
		nullptr,
		nullptr,
		functionName.c_str(),
		"ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS, //구식문법을 엄밀히 체크해서 금지시킴
		0,
		nullptr,
		&psBlob,
		&error,
		nullptr
	);
	assert(CheckShaderError(hr, error));

	hr = graphics->GetDevice()->CreatePixelShader
	(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		nullptr,
		&pixelShader
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(error);
}

void PixelShader::Clear()
{
	SAFE_RELEASE(pixelShader);
}

void PixelShader::BindPipeline()
{
	graphics->GetDeviceContext()->PSSetShader(pixelShader, nullptr, 0);
}
