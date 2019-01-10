#pragma once

class BoundBox
{
public:
	BoundBox();
	BoundBox(const Vector3& min, const Vector3& max);
	BoundBox(const vector<struct VertexTexture>& vertices);
	virtual ~BoundBox();

	const Vector3& GetMin() const { return minPoint; }
	const Vector3& GetMax() const { return maxPoint; }
	const Vector3 GetCenter() const { return (maxPoint + minPoint) * 0.5f; }
	const Vector3 GetSize() const { return maxPoint - minPoint; }
	const Vector3 GetExtents() const { return (maxPoint - minPoint) * 0.5f; }

	const Intersection IsInside(const Vector3& point);
	const Intersection IsInside(const BoundBox& box);

	const BoundBox Transformed(const Matrix& transform);

private:
	Vector3 minPoint;
	Vector3 maxPoint;
};