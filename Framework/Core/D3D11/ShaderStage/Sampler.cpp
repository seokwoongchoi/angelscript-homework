#include "stdafx.h"
#include "Sampler.h"

Sampler::Sampler(Context * context)
	: state(nullptr)
	, filter(D3D11_FILTER_ANISOTROPIC)
	, addressMode(D3D11_TEXTURE_ADDRESS_WRAP)
	, comparisonFunc(D3D11_COMPARISON_ALWAYS)
{
	graphics = context->GetSubsystem<Graphics>();
}

Sampler::~Sampler()
{
	Clear();
}

void Sampler::Create(const ShaderType & shaderType, const uint & slot, const D3D11_FILTER & filter, const D3D11_TEXTURE_ADDRESS_MODE addressMode, const D3D11_COMPARISON_FUNC & comparisonFunc)
{
	this->shaderType = shaderType;
	this->slot = slot;
	this->filter = filter;
	this->addressMode = addressMode;
	this->comparisonFunc = comparisonFunc;

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	
	samplerDesc.Filter = filter;
	samplerDesc.AddressU = addressMode;
	samplerDesc.AddressV = addressMode;
	samplerDesc.AddressW = addressMode;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = comparisonFunc;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = FLT_MIN;
	samplerDesc.MaxLOD = FLT_MAX;

	HRESULT hr = graphics->GetDevice()->CreateSamplerState(&samplerDesc, &state);
	assert(SUCCEEDED(hr));
}

void Sampler::Clear()
{
	SAFE_RELEASE(state);
	filter = D3D11_FILTER_ANISOTROPIC;
	addressMode = D3D11_TEXTURE_ADDRESS_WRAP;
	comparisonFunc = D3D11_COMPARISON_ALWAYS;
}

void Sampler::BindPipeline()
{
	auto dc = graphics->GetDeviceContext();

	switch (shaderType)
	{
	case ShaderType::VS: dc->VSSetSamplers(slot, 1, &state); break;
	case ShaderType::PS: dc->PSSetSamplers(slot, 1, &state); break;
	case ShaderType::GS: dc->GSSetSamplers(slot, 1, &state); break;
	case ShaderType::CS: dc->CSSetSamplers(slot, 1, &state); break;
	}
}
