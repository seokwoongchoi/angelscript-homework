#pragma once

class LineRenderer
{
public:
	LineRenderer(class Context* context);
	virtual ~LineRenderer();

	void AddLine
	(
		const Vector3& start,
		const Vector3& end,
		const D3DXCOLOR& color
	);
	void AddLine
	(
		const float& sx,
		const float& sy,
		const float& sz,
		const float& ex,
		const float& ey,
		const float& ez,
		const float& r,
		const float& g,
		const float& b,
		const float& a
	);
	void AddLines(const vector<VertexColor>& lines);
	void AddBoundBox(const BoundBox& box, const D3DXCOLOR& color);
	void Clear();

	void Update();
	void Render();

private:
	void AddVertex(const VertexColor& vertex);
	void AddVertex
	(
		const Vector3& position, 
		const D3DXCOLOR& color
	);
	void AddVertex
	(
		const float& x,
		const float& y,
		const float& z,
		const float& r,
		const float& g,
		const float& b,
		const float& a
	);

	void CreateVertexBuffer();
	void UpdateVertexBuffer();

private:
	class Context* context;
	class Shader* shader;
	class VertexBuffer* vertexBuffer;
	vector<VertexColor> vertices;
	uint vertexCount;
};