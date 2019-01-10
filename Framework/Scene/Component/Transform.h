#pragma once
#include "IComponent.h"

class Transform : public IComponent
{
public:
	Transform
	(
		class Context* context,
		class GameObject* object,
		class Transform* transform
	);
	virtual ~Transform();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;
	void OnSave()override;
	

	const Vector3& GetLocalScale() const { return localScale; }
	const Vector3& GetLocalRotate() const { return localRotate; }
	const Vector3& GetLocalPosition() const { return localPosition; }

	const Vector3 GetScale() { return world.GetScale(); }
	const Vector3 GetRotate() { return world.GetRotation(); }
	const Vector3 GetPosition() { return world.GetTranslation(); }

	const Vector3 GetRight();
	const Vector3 GetUp();
	const Vector3 GetForward();

	const Matrix& GetLocalMatrix() const { return local; }
	const Matrix& GetWorldMatrix() const { return world; }
	const Matrix GetRotationMatrix();

	Transform* GetRoot() { return HasParent() ? GetParent()->GetRoot() : this; }
	Transform* GetParent() { return parent; }
	Transform* GetChildFromIndex(const uint& index);
	const vector<Transform*>& GetChilds() const { return childs; }
	const uint GetChildCount() const { return childs.size(); }

	void SetLocalScale(const Vector3& vec);
	void SetLocalRotate(const Vector3& vec);
	void SetLocalPosition(const Vector3& vec);

	void SetScale(const Vector3& vec);
	void SetRotate(const Vector3& vec);
	void SetPosition(const Vector3& vec);

	void SetParent(Transform* newParent);
	void AddChild(Transform* child);

	const bool HasParent() const { return parent ? true : false; }
	const bool HasChild() const { return !childs.empty(); }

	void UpdateTransform();

private:
	Vector3 localScale;
	Vector3 localRotate;
	Vector3 localPosition;

	Matrix local;
	Matrix world;

	Transform* parent;
	vector<Transform*> childs;
private:
	Keyframe keyframe[10];
	class Animation* animation;
	class SceneManager* sceneManager;
	class Renderer* renderer;
	class ResourceManager* resourceManager;
	class Texture* texture;
	
	int loop;
	
};