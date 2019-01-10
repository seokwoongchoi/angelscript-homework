#pragma once

class Viewport
{
public:
	Viewport(class Context* context);
	virtual ~Viewport();

	void SetViewport(const float& width, const float& height);
	void SetViewport
	(
		const float& x,
		const float& y,
		const float& width,
		const float& height,
		const float& minDepth,
		const float& maxDepth
	);

	void BindPipeline();

private:
	class Graphics* graphics;
	D3D11_VIEWPORT viewport;
};