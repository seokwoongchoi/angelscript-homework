#include "stdafx.h"
#include "Viewport.h"

Viewport::Viewport(Context * context)
{
	graphics = context->GetSubsystem<Graphics>();
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
}

Viewport::~Viewport()
{
}

void Viewport::SetViewport(const float & width, const float & height)
{
	SetViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f);
}

void Viewport::SetViewport(const float & x, const float & y, const float & width, const float & height, const float & minDepth, const float & maxDepth)
{
	viewport.TopLeftX = x;
	viewport.TopLeftY = y;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = minDepth;
	viewport.MaxDepth = maxDepth;
}

void Viewport::BindPipeline()
{
	graphics->GetDeviceContext()->RSSetViewports(1, &viewport);
}
