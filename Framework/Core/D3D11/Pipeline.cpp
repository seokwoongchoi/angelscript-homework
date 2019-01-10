#include "stdafx.h"
#include "Pipeline.h"

Pipeline::Pipeline(Context * context)
	: inputLayout(nullptr)
	, vertexBuffer(nullptr)
	, indexBuffer(nullptr)
	, primitiveTopology(nullptr)
	, vertexShader(nullptr)
	, pixelShadser(nullptr)
	, bInputLayout(false)
	, bVertexBuffer(false)
	, bIndexBuffer(false)
	, bPrimitiveTopology(false)
	, bVertexShader(false)
	, bPixelShader(false)
{
	graphics = context->GetSubsystem<Graphics>();
}

Pipeline::~Pipeline()
{
}

void Pipeline::SetInputLayout(InputLayout * inputLayout)
{
	if (this->inputLayout != inputLayout)
	{
		this->inputLayout = inputLayout;
		bInputLayout = true;
	}
}

void Pipeline::SetVertexBuffer(VertexBuffer * vertexBuffer)
{
	if (this->vertexBuffer != vertexBuffer)
	{
		this->vertexBuffer = vertexBuffer;
		bVertexBuffer = true;
	}
}

void Pipeline::SetIndexBuffer(IndexBuffer * indexBuffer)
{
	if (this->indexBuffer != indexBuffer)
	{
		this->indexBuffer = indexBuffer;
		bIndexBuffer = true;
	}
}

void Pipeline::SetPrimitiveTopology(PrimitiveTopology * primitiveTopology)
{
	if (this->primitiveTopology != primitiveTopology)
	{
		this->primitiveTopology = primitiveTopology;
		bPrimitiveTopology = true;
	}
}

void Pipeline::SetVertexShader(VertexShader * vertexShader)
{
	if (this->vertexShader != vertexShader)
	{
		this->vertexShader = vertexShader;
		bVertexShader = true;
	}
}

void Pipeline::SetPixelShader(PixelShader * pixelShadser)
{
	if (this->pixelShadser != pixelShadser)
	{
		this->pixelShadser = pixelShadser;
		bPixelShader = true;
	}
}

void Pipeline::SetConstantBuffer(ConstantBuffer * cbuffer)
{
	constantBuffers.emplace_back(cbuffer);
}

void Pipeline::SetTexture(const ShaderType & type, Texture * texture)
{
	if (texture)
		textures[type].emplace_back(texture->GetShaderResourceView());
}

void Pipeline::BindPipeline()
{
	if (bInputLayout)
	{
		this->inputLayout->BindPipeline();
		bInputLayout = false;
	}

	if (bVertexBuffer)
	{
		this->vertexBuffer->BindPipeline();
		bVertexBuffer = false;
	}

	if (bIndexBuffer)
	{
		this->indexBuffer->BindPipeline();
		bIndexBuffer = false;
	}

	if (bPrimitiveTopology)
	{
		this->primitiveTopology->BindPipeline();
		bPrimitiveTopology = false;
	}

	if (bVertexShader)
	{
		this->vertexShader->BindPipeline();
		bVertexShader = false;
	}

	if (bPixelShader)
	{
		this->pixelShadser->BindPipeline();
		bPixelShader = false;
	}

	for (auto cbuffer : constantBuffers)
		cbuffer->BindPipeline();

	constantBuffers.clear();
	constantBuffers.shrink_to_fit();

	if (!textures.empty())
	{
		if (!textures[ShaderType::VS].empty())
		{
			graphics->GetDeviceContext()->VSSetShaderResources
			(
				0,
				textures[ShaderType::VS].size(),
				textures[ShaderType::VS].data()
			);
		}
		textures[ShaderType::VS].clear();
		textures[ShaderType::VS].shrink_to_fit();

		if (!textures[ShaderType::PS].empty())
		{
			graphics->GetDeviceContext()->PSSetShaderResources
			(
				0,
				textures[ShaderType::PS].size(),
				textures[ShaderType::PS].data()
			);
		}
		textures[ShaderType::PS].clear();
		textures[ShaderType::PS].shrink_to_fit();

		if (!textures[ShaderType::GS].empty())
		{
			graphics->GetDeviceContext()->GSSetShaderResources
			(
				0,
				textures[ShaderType::GS].size(),
				textures[ShaderType::GS].data()
			);
		}
		textures[ShaderType::GS].clear();
		textures[ShaderType::GS].shrink_to_fit();

		if (!textures[ShaderType::CS].empty())
		{
			graphics->GetDeviceContext()->CSSetShaderResources
			(
				0,
				textures[ShaderType::CS].size(),
				textures[ShaderType::CS].data()
			);
		}
		textures[ShaderType::CS].clear();
		textures[ShaderType::CS].shrink_to_fit();
	}

	textures.clear();
}
