#pragma once
#include "IComponent.h"

class Camera : public IComponent
{
public:
	Camera
	(
		class Context* context,
		class GameObject* object,
		class Transform* transform
	);
	Camera(class Context* context);
	virtual ~Camera();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;
	void OnSave()override;
	

	void EditorCameraUpdate();

	const Matrix& GetViewMatrix() const { return view; }
	const Matrix& GetProjMatrix() const { return proj; }
	const float& GetNearPlane() const { return nearPlane; }
	const float& GetFarPlane() const { return farPlane; }

	void SetNearPlane(const float& nearPlane) { this->nearPlane = nearPlane; }
	void SetFarPlane(const float& farPlane) { this->farPlane = farPlane; }

	const Vector3 ScreenToWorldPoint(const Vector2& screenPoint);
	
	const bool& IsEditorCamera()const { return bEditorCamera; }
private:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:
	class Timer* timer;
	class Input* input;

	Vector3 position;
	Matrix view;
	Matrix proj;
	float nearPlane;
	float farPlane;
	float zoom;

	bool bEditorCamera;
};