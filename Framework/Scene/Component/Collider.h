#pragma once

enum class ColliderType : uint
{
	Square, Circle
};

class Collider
{
public:
	Collider(class Context* context);
	virtual ~Collider();

	class Transform* GetTransform() const { return transform; }
	const ColliderType& GetColliderType() const { return colliderType; }
	const Vector3& GetCenter() const { return center; }
	const Vector3& GetSize() const { return size; }

	const BoundBox GetBoundBox() const;

	void SetTransform(class Transform* transform) { this->transform = transform; }
	void SetColliderType(const ColliderType& colliderType) { this->colliderType = colliderType; }
	void SetCenter(const Vector3& center) { this->center = center; }
	void SetSize(const Vector3& size) { this->size = size; }


	const bool AABB(Collider* collider);
	const bool OBB(Collider* collider);

	void Update();

public:
	function<void()> Event;

private:
	class Context* context;
	class Transform* transform;
	ColliderType colliderType;
	Vector3 center;
	Vector3 size;
};