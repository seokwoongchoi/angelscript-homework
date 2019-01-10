#include "stdafx.h"
#include "Gizmo.h"
#include "../ImGui/Source/imgui.h"
#include "../ImGui/ImGuizmo.h"
#include "../../Framework/Scene/Component/Camera.h"
#include "../../Framework/Scene/Component/Transform.h"

void Gizmo::TransformGizmo(Camera * camera, Transform * transform, const Vector2 & framePos, const Vector2 & frameSize)
{
	if (!camera || !transform)
		return;

	static ImGuizmo::OPERATION operation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mode(ImGuizmo::WORLD);

	if (ImGui::IsKeyPressed(87)) // w
		operation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69)) // e
		operation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) // r
		operation = ImGuizmo::SCALE;

	auto matrix = transform->GetWorldMatrix().Transpose();

	ImGuizmo::SetOrthographic(true);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(framePos.x, framePos.y, frameSize.x, frameSize.y);
	ImGuizmo::Manipulate
	(
		camera->GetViewMatrix(),
		camera->GetProjMatrix(),
		operation,
		mode,
		matrix
	);

	matrix.Transpose();
	transform->SetScale(matrix.GetScale());
	transform->SetPosition(matrix.GetTranslation());
	transform->SetRotate(matrix.GetRotation());
}
