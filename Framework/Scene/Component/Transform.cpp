#include "stdafx.h"
#include "Transform.h"
#include "Framework/Scene/Scene.h"
#include "Framework/Scene/GameObject.h"

Transform::Transform(Context * context, GameObject * object, Transform * transform)
	: IComponent(context, object, transform)
	, localScale(1, 1, 1)
	, localRotate(0, 0, 0)
	, localPosition(0, 0, 0)
	, parent(nullptr)
	, animation(nullptr)
	,loop(0)
	{
	
	local.SetIdentity();
	world.SetIdentity();
	resourceManager = context->GetSubsystem<ResourceManager>();
	sceneManager = context->GetSubsystem<SceneManager>();
	animation = new Animation(context);
}

Transform::~Transform()
{
	SAFE_DELETE(animation);
}

void Transform::OnInitialize()
{
}

void Transform::OnStart()
{
}

void Transform::OnUpdate()
{
	
}

void Transform::OnStop()
{
}

void Transform::OnDestroy()
{
}

void Transform::OnSave()
{
	if (!object) return;
	
	
	auto objects = sceneManager->GetCurrentScene()->GetObjects();
	for (int i =1; i< objects.size(); i++)
	{
		keyframe[loop].texture = resourceManager->Load<Texture>("tree.png");

		keyframe[loop].offset.x = objects[i]->GetTransform()->GetPosition().x;
		keyframe[loop].offset.y = objects[i]->GetTransform()->GetPosition().y;


		keyframe[loop].size.x = objects[i]->GetTransform()->GetScale().x;
		keyframe[loop].size.y = objects[i]->GetTransform()->GetScale().y;
		keyframe[loop].time = 100;

		animation->AddKeyframe(keyframe[loop]);
		loop++;
	}
	
	animation->SaveToFile("Save.xml");
}




const Vector3 Transform::GetRight()
{
	return Vector3::TransformNormal
	(
		Vector3::Right,
		GetRotationMatrix()
	);
}

const Vector3 Transform::GetUp()
{
	return Vector3::TransformNormal
	(
		Vector3::Up,
		GetRotationMatrix()
	);
}

const Vector3 Transform::GetForward()
{
	return Vector3::TransformNormal
	(
		Vector3::Forward,
		GetRotationMatrix()
	);
}

const Matrix Transform::GetRotationMatrix()
{
	Vector3 scale = GetScale();

	bool bCheck = true;
	bCheck &= scale.x == 0.0f;
	bCheck &= scale.y == 0.0f;
	bCheck &= scale.z == 0.0f;

	if (bCheck)
		return Matrix();

	float factorX = 1.0f / scale.x;
	float factorY = 1.0f / scale.y;
	float factorZ = 1.0f / scale.z;

	return Matrix
	(
		world._11 * factorX, world._12 * factorX, world._13 * factorX, world._14 * factorX,
		world._21 * factorY, world._22 * factorY, world._23 * factorY, world._24 * factorY,
		world._31 * factorZ, world._32 * factorZ, world._33 * factorZ, world._34 * factorZ,
		0, 0, 0, 1
	);
}

Transform * Transform::GetChildFromIndex(const uint & index)
{
	if (!HasChild())
		return nullptr;

	if (index >= childs.size())
		return nullptr;

	return childs[index];
}

void Transform::SetLocalScale(const Vector3 & vec)
{
	if (localScale == vec)
		return;

	localScale = vec;
	UpdateTransform();
}

void Transform::SetLocalRotate(const Vector3 & vec)
{
	if (localRotate == vec)
		return;

	localRotate = vec;
	UpdateTransform();
}

void Transform::SetLocalPosition(const Vector3 & vec)
{
	if (localPosition == vec)
		return;

	localPosition = vec;
	UpdateTransform();
}

void Transform::SetScale(const Vector3 & vec)
{
	if (GetScale() == vec)
		return;

	if (HasParent())
	{
		Vector3 parentScale = parent->GetScale();
		Vector3 scale;
		scale.x = vec.x / parentScale.x;
		scale.y = vec.y / parentScale.y;
		scale.z = vec.z / parentScale.z;

		SetLocalScale(scale);
	}
	else
		SetLocalScale(vec);
}

void Transform::SetRotate(const Vector3 & vec)
{
	if (GetRotate() == vec)
		return;

	if (HasParent())
	{
		Matrix inv = Matrix::Inverse(parent->GetRotationMatrix());
		SetLocalRotate(Vector3::TransformNormal(vec, inv));
	}
	else
		SetLocalRotate(vec);

	
}

void Transform::SetPosition(const Vector3 & vec)
{
	if (GetPosition() == vec)
		return;

	if (HasParent())
	{
		Matrix inv = Matrix::Inverse(parent->GetWorldMatrix());
		SetLocalPosition(Vector3::TransformCoord(vec, inv));
	}
	else
		SetLocalPosition(vec);
}

void Transform::SetParent(Transform * newParent)
{
	if (!newParent)
		return;

	if (newParent == this)
		return;

	//TODO : 이전 부모가 있었으면 그부모에서 자기를 제거 시키는것 만들기

	parent = newParent;
	parent->AddChild(this);
}

void Transform::AddChild(Transform * child)
{
	if (!child)
		return;

	if (child == this)
		return;

	child->SetParent(this);
	childs.push_back(child);
}

void Transform::UpdateTransform()
{
	Matrix S = Matrix::Scaling(localScale);
	Matrix R = Matrix::RotationYawPitchRoll(localRotate);
	Matrix T = Matrix::Translation(localPosition);

	local = S * R * T;

	if (HasParent())
		world = local * parent->GetWorldMatrix();
	else
		world = local;

	for (const auto& child : childs)
		child->UpdateTransform();
}
