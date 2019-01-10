#include "stdafx.h"
#include "PrimitiveTopology.h"

PrimitiveTopology::PrimitiveTopology(Context * context)
	: topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	graphics = context->GetSubsystem<Graphics>();
}

PrimitiveTopology::~PrimitiveTopology()
{
}

void PrimitiveTopology::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY & topology)
{
	this->topology = topology;
}

void PrimitiveTopology::BindPipeline()
{
	graphics->GetDeviceContext()->IASetPrimitiveTopology(topology);
}
