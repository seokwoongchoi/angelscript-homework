#include "stdafx.h"
#include "BoundBox.h"
#include "../Core/D3D11/Vertex.h"

BoundBox::BoundBox()
{
	minPoint = Vector3
	(
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity()
	);

	maxPoint = Vector3
	(
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity()
	);
}

BoundBox::BoundBox(const Vector3 & min, const Vector3 & max)
	: minPoint(min)
	, maxPoint(max)
{
}

BoundBox::BoundBox(const vector<VertexTexture>& vertices)
{
	minPoint = Vector3
	(
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity()
	);

	maxPoint = Vector3
	(
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity()
	);

	for (auto& vertex : vertices)
	{
		minPoint.x = Math::Min(minPoint.x, vertex.Position.x);
		minPoint.y = Math::Min(minPoint.y, vertex.Position.y);
		minPoint.z = Math::Min(minPoint.z, vertex.Position.z);

		maxPoint.x = Math::Max(maxPoint.x, vertex.Position.x);
		maxPoint.y = Math::Max(maxPoint.y, vertex.Position.y);
		maxPoint.z = Math::Max(maxPoint.z, vertex.Position.z);
	}
}

BoundBox::~BoundBox()
{
}

const Intersection BoundBox::IsInside(const Vector3 & point)
{
	if (
		point.x < minPoint.x || point.x > maxPoint.x ||
		point.y < minPoint.y || point.y > maxPoint.y ||
		point.z < minPoint.z || point.z > maxPoint.z)
		return Intersection::Outside;

	return Intersection::Inside;
}

const Intersection BoundBox::IsInside(const BoundBox & box)
{
	if (
		box.maxPoint.x < minPoint.x || box.minPoint.x > maxPoint.x ||
		box.maxPoint.y < minPoint.y || box.minPoint.y > maxPoint.y ||
		box.maxPoint.z < minPoint.z || box.minPoint.z > maxPoint.z)
		return Intersection::Outside;
	else if (
		box.minPoint.x < minPoint.x || box.maxPoint.x > maxPoint.x ||
		box.minPoint.y < minPoint.y || box.maxPoint.y > maxPoint.y ||
		box.minPoint.z < minPoint.z || box.maxPoint.z > maxPoint.z)
		return Intersection::Intersect;
	else
		return Intersection::Inside;
}

const BoundBox BoundBox::Transformed(const Matrix & transform)
{
	Vector3 newCenter = Vector3::TransformCoord(GetCenter(), transform);

	Vector3 oldEdge = GetSize() * 0.5f;
	Vector3 newEdge = Vector3
	(
		Math::Abs(transform._11) * oldEdge.x + Math::Abs(transform._21) * oldEdge.y + Math::Abs(transform._31) * oldEdge.z,
		Math::Abs(transform._12) * oldEdge.x + Math::Abs(transform._22) * oldEdge.y + Math::Abs(transform._32) * oldEdge.z,
		Math::Abs(transform._13) * oldEdge.x + Math::Abs(transform._23) * oldEdge.y + Math::Abs(transform._33) * oldEdge.z
	);

	return BoundBox(newCenter - newEdge, newCenter + newEdge);
}
