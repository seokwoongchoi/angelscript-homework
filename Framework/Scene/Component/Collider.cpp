#include "stdafx.h"
#include "Collider.h"

Collider::Collider(Context * context)
	: context(context)
	, transform(nullptr)
	, Event(nullptr)
	, colliderType(ColliderType::Square)
	, center(0, 0, 0)
	, size(0, 0, 0)
{
}

Collider::~Collider()
{
}

const BoundBox Collider::GetBoundBox() const
{
	Vector3 minPoint = Vector3
	(
		center.x - size.x * 0.5f,
		center.y - size.y * 0.5f,
		center.z - size.z * 0.5f
	);

	Vector3 maxPoint = Vector3
	(
		center.x + size.x * 0.5f,
		center.y + size.y * 0.5f,
		center.z + size.z * 0.5f
	);

	return BoundBox(minPoint, maxPoint);
}

const bool Collider::AABB(Collider * collider)
{
	BoundBox boundBox = GetBoundBox();

	auto check = boundBox.IsInside(collider->GetBoundBox());
	return static_cast<uint>(check) > 0;
}

const bool Collider::OBB(Collider * collider)
{
	//TODO :
	return false;
}

void Collider::Update()
{
}
