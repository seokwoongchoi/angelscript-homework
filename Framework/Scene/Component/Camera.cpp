#include "stdafx.h"
#include "Camera.h"
#include "Transform.h"

Camera::Camera(Context * context, GameObject * object, Transform * transform)
	: IComponent(context, object, transform)
	,timer(nullptr)
	,input(nullptr)
	, nearPlane(0.0f)
	, farPlane(1.0f)
	,zoom(1.0f)
	,bEditorCamera(false)
{
	view.SetIdentity();
	proj.SetIdentity();
}

Camera::Camera(Context * context)
	:IComponent(context, nullptr, nullptr)
	, nearPlane(0.0f)
	, farPlane(1.0f)
	, zoom(1.0f)
	, bEditorCamera(true)
{
	timer = context->GetSubsystem<Timer>();
	input = context->GetSubsystem<Input>();
	transform = new Transform(context, nullptr, nullptr);
	view.SetIdentity();
	proj.SetIdentity();
}

Camera::~Camera()
{
	if (bEditorCamera)
		SAFE_DELETE(transform);
}

void Camera::OnInitialize()
{
}

void Camera::OnStart()
{
}

void Camera::OnUpdate()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::OnStop()
{
}

void Camera::OnDestroy()
{
}

void Camera::OnSave()
{
}





void Camera::EditorCameraUpdate()
{
	if (!bEditorCamera)return;

	Vector3 position = transform->GetPosition();
	Vector3 right = transform->GetRight();
	Vector3 up = transform->GetUp();

	if (input->KeyPress(VK_Shift))
	{
		if (input->KeyPress(VK_Shift))
		{
			if (input->KeyPress(VK_W))
				position += up * 200.0f*timer->GetDeltaTimeSec();
			else if (input->KeyPress(VK_S))
				position -= up * 200.0f*timer->GetDeltaTimeSec();

			if (input->KeyPress(VK_A))
				position -= right * 200.0f*timer->GetDeltaTimeSec();
			else if (input->KeyPress(VK_D))
				position += right * 200.0f*timer->GetDeltaTimeSec();

		}
	}
		transform->SetPosition(position);

		float delta = input->GetMouseMoveValue().z;
		if (Math::Abs(delta) >= WHEEL_DELTA)
		{
			float deltaZoom = 1.0f - Math::Abs(delta) / WHEEL_DELTA / 10.f;
			if (delta < 0)
				zoom *= deltaZoom;
			else
				zoom /= deltaZoom;
			Math::Clamp(zoom, 0.1f, 100.0f);
		}
		UpdateViewMatrix();
		UpdateProjectionMatrix();
}

const Vector3 Camera::ScreenToWorldPoint(const Vector2 & screenPoint)
{
	auto viewport = Settings::Get()->GetRelative();

	//Convert Screen pixel to view space
	float pointX = +2.0f * screenPoint.x / viewport.x - 1.0f;
	float pointY = -2.0f * screenPoint.y / viewport.y + 1.0f;

	//Unprojection point
	Matrix unprojection = (view * proj).Inverse();

	return Vector3::TransformCoord
	(
		Vector3(pointX, pointY, 0.0f),
		unprojection
	);
}

void Camera::UpdateViewMatrix()
{
	Vector3 position = transform->GetPosition();
	Vector3 forward = transform->GetForward();
	Vector3 up = transform->GetUp();

	view = Matrix::LookAtLH(position, (position + forward), up);
}

void Camera::UpdateProjectionMatrix()
{
	auto viewport = Settings::Get()->GetViewport();

	proj = Matrix::OrthoLH
	(
		viewport.Width/zoom,
		viewport.Height/zoom,
		nearPlane,
		farPlane
	);
}
