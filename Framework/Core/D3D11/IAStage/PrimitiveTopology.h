#pragma once

class PrimitiveTopology
{
public:
	PrimitiveTopology(class Context* context);
	virtual ~PrimitiveTopology();

	void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology);

	void BindPipeline();

private:
	class Graphics* graphics;
	D3D11_PRIMITIVE_TOPOLOGY topology;
};