#include "stdafx.h"
#include "LineRenderer.h"

LineRenderer::LineRenderer(Context * context)
	: context(context)
	, vertexCount(0)
{
	vertexBuffer = new VertexBuffer(context->GetSubsystem<Graphics>());
	shader =
		context->GetSubsystem<ResourceManager>()->Load<Shader>("Line.hlsl");
}

LineRenderer::~LineRenderer()
{
	SAFE_DELETE(vertexBuffer);
}

void LineRenderer::AddLine(const Vector3 & start, const Vector3 & end, const D3DXCOLOR & color)
{
	AddVertex(start, color);
	AddVertex(end, color);
}

void LineRenderer::AddLine(const float & sx, const float & sy, const float & sz, const float & ex, const float & ey, const float & ez, const float & r, const float & g, const float & b, const float & a)
{
	AddVertex(sx, sy, sz, r, g, b, a);
	AddVertex(ex, ey, ez, r, g, b, a);
}

void LineRenderer::AddLines(const vector<VertexColor>& lines)
{
	vertices.insert(vertices.end(), lines.begin(), lines.end());
}

void LineRenderer::AddBoundBox(const BoundBox & box, const D3DXCOLOR & color)
{
	//minx, maxy -2   maxx, maxy - 3
	//minx, miny -1	  maxx, miny - 4

	Vector3 boundPoint1 = box.GetMin();
	Vector3 boundPoint2 = Vector3(box.GetMin().x, box.GetMax().y, 0.0f);
	Vector3 boundPoint3 = box.GetMax();
	Vector3 boundPoint4 = Vector3(box.GetMax().x, box.GetMin().y, 0.0f);
	
	AddLine(boundPoint1, boundPoint2, color);
	AddLine(boundPoint2, boundPoint3, color);
	AddLine(boundPoint3, boundPoint4, color);
	AddLine(boundPoint4, boundPoint1, color);
}

void LineRenderer::Clear()
{
}

void LineRenderer::Update()
{
	if (vertexCount != vertices.size())
	{
		vertexCount = vertices.size();
		CreateVertexBuffer();
		UpdateVertexBuffer();
	}
}

void LineRenderer::Render()
{
	vertexBuffer->BindPipeline();
	shader->BindPipeline();

	auto graphcis = context->GetSubsystem<Graphics>();
	graphcis->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	graphcis->GetDeviceContext()->Draw(vertexCount, 0);
}

void LineRenderer::AddVertex(const VertexColor & vertex)
{
	vertices.emplace_back(vertex);
}

void LineRenderer::AddVertex(const Vector3 & position, const D3DXCOLOR & color)
{
	AddVertex(VertexColor(position, color));
}

void LineRenderer::AddVertex(const float & x, const float & y, const float & z, const float & r, const float & g, const float & b, const float & a)
{
	AddVertex(Vector3(x, y, z), D3DXCOLOR(r, g, b, a));
}

void LineRenderer::CreateVertexBuffer()
{
	vertexBuffer->Clear();
	vertexBuffer->Create<VertexColor>(vertices, D3D11_USAGE_DYNAMIC);
}

void LineRenderer::UpdateVertexBuffer()
{
	auto data = vertexBuffer->Map();
	memcpy(data, vertices.data(), sizeof(VertexColor) * vertices.size());
	vertexBuffer->Unmap();
}