#include "stdafx.h"
#include "Widget_Scene.h"
#include "../Utility/EditorHelper.h"
#include "../Utility/Gizmo.h"
#include "../Utility/DragDrop.h"
#include "../../Framework/Scene/Scene.h"
#include "../../Framework/Scene/GameObject.h"
#include "../../Framework/Scene/Component/Camera.h"
#include "../../Framework/Scene/Component/Transform.h"
#include "../../Framework/Scene/Component/Renderable.h"
#include "Framework/Resource/Animation.h"

Widget_Scene::Widget_Scene()
{
}

Widget_Scene::~Widget_Scene()
{
}

void Widget_Scene::Initialize(Context * context)
{
	__super::Initialize(context);
	title = "Scene";
	windowFlags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

	camera = nullptr;
	sceneManager = context->GetSubsystem<SceneManager>();
	renderer = context->GetSubsystem<Renderer>();
	resourceManager = context->GetSubsystem<ResourceManager>();
	texture = nullptr;
	animation = nullptr;
	
}

void Widget_Scene::Render()
{
	ShowFrame();
	ShowGizmo();
	
	Picking();
	DragDrop();
}

void Widget_Scene::ShowFrame()
{
	framePos = EditorHelper::ToDxVec2
	(
		ImGui::GetCursorPos() + 
		ImGui::GetWindowPos()
	);

	frameSize = EditorHelper::ToDxVec2
	(
		ImGui::GetWindowContentRegionMax() - 
		ImGui::GetWindowContentRegionMin()
	);

	frameSize.x -= static_cast<float>((static_cast<int>(frameSize.x) % 2 != 0) ? 1 : 0);
	frameSize.y -= static_cast<float>((static_cast<int>(frameSize.y) % 2 != 0) ? 1 : 0);

	ImGui::Image
	(
		renderer->GetFrameResource(),
		EditorHelper::ToImVec2(frameSize),
		ImVec2(0, 0),
		ImVec2(1, 1),
		ImVec4(1, 1, 1, 1),
		ImColor(50, 127, 166, 255)
	);

	if (Settings::Get()->GetRelative() != frameSize)
		Settings::Get()->SetRelative(frameSize);

	/*auto mainCamera = sceneManager->GetCurrentScene()->GetMainCamera();
	camera = mainCamera->GetComponent<Camera>();*/
	camera = renderer->GetMainCamera();
}

void Widget_Scene::ShowGizmo()
{
	if (!EditorHelper::CurrentObject || !camera)
		return;

	Gizmo::TransformGizmo
	(
		camera,
		EditorHelper::CurrentObject->GetComponent<Transform>(),
		framePos,
		frameSize
	);
}

void Widget_Scene::Picking()
{
	bool bCheck = false;
	bCheck |= !camera;
	bCheck |= !ImGui::IsMouseClicked(0);
	bCheck |= !ImGui::IsWindowHovered
	(
		ImGuiHoveredFlags_AllowWhenBlockedByPopup |
		ImGuiHoveredFlags_AllowWhenBlockedByActiveItem
	);

	if (bCheck)
		return;

	Vector2 relativeMousePos
		= EditorHelper::ToDxVec2(ImGui::GetMousePos()) - framePos;
	Vector3 worldMousePos
		= camera->ScreenToWorldPoint(relativeMousePos);

	auto objects = sceneManager->GetCurrentScene()->GetObjects();
	for (auto object : objects)
	{
		if (!object->HasComponent<Renderable>())
			continue;

		auto renderalble = object->GetComponent<Renderable>();
		auto boundBox = renderalble->GetBoundBox();
		boundBox = boundBox.Transformed(object->GetComponent<Transform>()->GetWorldMatrix());

		auto result = boundBox.IsInside(worldMousePos);
		if (result == Intersection::Inside)
		{
		    EditorHelper::CurrentObject = object;
			
		}


	}
//===================================================================================
	
	
}

void Widget_Scene::DragDrop()
{
	string data = DragDrop::GetDragDropPayload(DragDropPayloadType::Texture);

	if (data.length() != 0)
	{
		if (EditorHelper::CurrentObject)
		{
			auto renderable = EditorHelper::CurrentObject->GetComponent<Renderable>();
			auto material = renderable->GetMaterial();

			material->SetDiffuseTexture(data);
		}
	}
}


