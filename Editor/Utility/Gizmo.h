#pragma once

class Gizmo
{
public:
	static void TransformGizmo
	(
		class Camera* camera,
		class Transform* transform,
		const Vector2& framePos,
		const Vector2& frameSize
	);
};