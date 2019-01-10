#include "stdafx.h"
#include "ScriptInterface.h"
#include <AngelScript\angelscript.h>
#include "../Scene/GameObject.h"
#include "../Scene/Component/Camera.h"
#include "../Scene/Component/Transform.h"
#include "../Scene/Component/Renderable.h"

void ScriptInterface::Register(Context * context, asIScriptEngine * scriptEngine)
{
	this->context = context;
	this->scriptEngine = scriptEngine;

	RegisterEnumerations();
	RegisterTypes();
	RegisterSettings();
	RegisterTimer();
	RegisterInput();
	RegisterGameObject();
	RegisterTransform();
	RegisterRenderable();
	RegisterMaterial();
	RegisterCamera();
	RegisterMath();
	RegisterVector2();
	RegisterVector3();
}

void ScriptInterface::RegisterEnumerations()
{
	//Components Type
	scriptEngine->RegisterEnum("ComponentType");
	scriptEngine->RegisterEnumValue("ComponentType", "Camera", uint(ComponentType::Camera));
	scriptEngine->RegisterEnumValue("ComponentType", "Renderable", uint(ComponentType::Renderable));
	scriptEngine->RegisterEnumValue("ComponentType", "Transform", uint(ComponentType::Transform));
	scriptEngine->RegisterEnumValue("ComponentType", "Animator", uint(ComponentType::Animator));
	scriptEngine->RegisterEnumValue("ComponentType", "AudioSource", uint(ComponentType::AudioSource));
	scriptEngine->RegisterEnumValue("ComponentType", "AudioListener", uint(ComponentType::AudioListener));
	scriptEngine->RegisterEnumValue("ComponentType", "Collider", uint(ComponentType::Collider));
	scriptEngine->RegisterEnumValue("ComponentType", "LineRenderer", uint(ComponentType::LineRenderer));
	scriptEngine->RegisterEnumValue("ComponentType", "Unknown", uint(ComponentType::Unknown));

	scriptEngine->RegisterEnum("VirtualKey");
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_0", DWORD(VK_0));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_1", DWORD(VK_1));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_2", DWORD(VK_2));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_3", DWORD(VK_3));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_4", DWORD(VK_4));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_5", DWORD(VK_5));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_6", DWORD(VK_6));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_7", DWORD(VK_7));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_8", DWORD(VK_8));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_9", DWORD(VK_9));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_A", DWORD(VK_A));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_B", DWORD(VK_B));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_C", DWORD(VK_C));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_D", DWORD(VK_D));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_E", DWORD(VK_E));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_F", DWORD(VK_F));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_G", DWORD(VK_G));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_H", DWORD(VK_H));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_I", DWORD(VK_I));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_J", DWORD(VK_J));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_K", DWORD(VK_K));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_L", DWORD(VK_L));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_M", DWORD(VK_M));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_N", DWORD(VK_N));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_O", DWORD(VK_O));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_P", DWORD(VK_P));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_Q", DWORD(VK_Q));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_R", DWORD(VK_R));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_S", DWORD(VK_S));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_T", DWORD(VK_T));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_U", DWORD(VK_U));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_V", DWORD(VK_V));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_W", DWORD(VK_W));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_X", DWORD(VK_X));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_Y", DWORD(VK_Y));
	scriptEngine->RegisterEnumValue("VirtualKey", "VK_Z", DWORD(VK_Z));
}

void ScriptInterface::RegisterTypes()
{
	scriptEngine->RegisterInterface("ScriptBehavior");

	scriptEngine->RegisterObjectType("Settings", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Input", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Timer", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("GameObject", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Transform", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Camera", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Renderable", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Math", 0, asOBJ_REF | asOBJ_NOCOUNT);
	scriptEngine->RegisterObjectType("Material", 0, asOBJ_REF | asOBJ_NOCOUNT);

	scriptEngine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR);
	scriptEngine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR);
}

void ScriptInterface::RegisterSettings()
{
}

void ScriptInterface::RegisterInput()
{
	scriptEngine->RegisterGlobalProperty("Input input", context->GetSubsystem<Input>());
	//scriptEngine->RegisterObjectMethod("Input", "Vector2 GetMousePosition()", asMETHOD(Input, GetMousePosition), asCALL_THISCALL);
	//scriptEngine->RegisterObjectMethod("Input", "Vector2 GetMouseDelta()", asMETHOD(Input, GetMouseDelta), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Input", "bool KeyPress(VirtualKey key)", asMETHOD(Input, KeyPress), asCALL_THISCALL);
}

void ScriptInterface::RegisterTimer()
{
	scriptEngine->RegisterGlobalProperty("Timer timer", context->GetSubsystem<Timer>());
	scriptEngine->RegisterObjectMethod("Timer", "const float& GetDeltaTime()", asMETHOD(Timer, GetDeltaTimeSec), asCALL_THISCALL);
}

void ScriptInterface::RegisterGameObject()
{
	scriptEngine->RegisterObjectMethod("GameObject", "GameObject &opAssign(const GameObject &in)", asMETHODPR(GameObject, operator =, (const GameObject&), GameObject&), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "string GetName()", asMETHOD(GameObject, GetName), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "void SetName(string)", asMETHOD(GameObject, SetName), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "bool IsActive()", asMETHOD(GameObject, IsActive), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "void SetIsActive(bool)", asMETHOD(GameObject, SetIsActive), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "Camera &GetCamera()", asMETHOD(GameObject, GetComponent<Camera>), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "Transform &GetTransform()", asMETHOD(GameObject, GetTransform), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("GameObject", "Renderable &GetRenderable()", asMETHOD(GameObject, GetComponent<Renderable>), asCALL_THISCALL);
}

void ScriptInterface::RegisterTransform()
{
	scriptEngine->RegisterObjectMethod("Transform", "Transform &opAssign(const Transform &in)", asMETHODPR(Transform, operator =, (const Transform&), Transform&), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetPosition()", asMETHOD(Transform, GetPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "void SetPosition(const Vector3& in)", asMETHOD(Transform, SetPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetLocalPosition()", asMETHOD(Transform, GetLocalPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "void SetLocalPosition(Vector3)", asMETHOD(Transform, SetLocalPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetScale()", asMETHOD(Transform, GetScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "void SetScale(Vector3)", asMETHOD(Transform, SetScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetLocalScale()", asMETHOD(Transform, GetLocalScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "void SetLocalScale(Vector3)", asMETHOD(Transform, SetLocalScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetRotate()", asMETHOD(Transform, GetRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "void SetRotate(Vector3)", asMETHOD(Transform, SetRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetLocalRotate()", asMETHOD(Transform, GetLocalRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "void SetLocalRotate(Vector3)", asMETHOD(Transform, SetLocalRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetUp()", asMETHOD(Transform, GetUp), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetForward()", asMETHOD(Transform, GetForward), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Vector3 GetRight()", asMETHOD(Transform, GetRight), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Transform &GetRoot()", asMETHOD(Transform, GetRoot), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Transform &GetParent()", asMETHOD(Transform, GetParent), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "Transform &GetChildFromIndex(int)", asMETHOD(Transform, GetChildFromIndex), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Transform", "GameObject &GetGameObject()", asMETHOD(Transform, GetGameObject), asCALL_THISCALL);

}

void ScriptInterface::RegisterRenderable()
{
	/*scriptEngine->RegisterObjectMethod("Renderable", "Renderable &opAssign(const Transform &in)", asMETHOD(Renderable, operator =, (const Renderable&), Renderable&), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetPosition()", asMETHOD(Renderable, GetPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "void SetPosition(const Vector3& in)", asMETHOD(Transform, SetPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetLocalPosition()", asMETHOD(Transform, GetLocalPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "void SetLocalPosition(Vector3)", asMETHOD(Transform, SetLocalPosition), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetScale()", asMETHOD(Transform, GetScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "void SetScale(Vector3)", asMETHOD(Transform, SetScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetLocalScale()", asMETHOD(Transform, GetLocalScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "void SetLocalScale(Vector3)", asMETHOD(Transform, SetLocalScale), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetRotate()", asMETHOD(Transform, GetRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "void SetRotate(Vector3)", asMETHOD(Transform, SetRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetLocalRotate()", asMETHOD(Transform, GetLocalRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "void SetLocalRotate(Vector3)", asMETHOD(Transform, SetLocalRotate), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetUp()", asMETHOD(Transform, GetUp), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetForward()", asMETHOD(Transform, GetForward), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Vector3 GetRight()", asMETHOD(Transform, GetRight), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Transform &GetRoot()", asMETHOD(Transform, GetRoot), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Transform &GetParent()", asMETHOD(Transform, GetParent), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "Transform &GetChildFromIndex(int)", asMETHOD(Transform, GetChildFromIndex), asCALL_THISCALL);
	scriptEngine->RegisterObjectMethod("Renderable", "GameObject &GetGameObject()", asMETHOD(Transform, GetGameObject), asCALL_THISCALL);*/
}

void ScriptInterface::RegisterMaterial()
{
}

void ScriptInterface::RegisterCamera()
{
}

void ScriptInterface::RegisterMath()
{
	scriptEngine->RegisterGlobalFunction(
		"float Random(const float& in,const float& in)",
		asFUNCTIONPR(Math::Random, (const float&, const float&), const float), asCALL_CDECL
	);
}

void ConstructorVector2(Vector2* other)
{
	new(other) Vector2(0, 0);
}

void CopyConstructorVector2(const Vector2& in, Vector2* other)
{
	new(other) Vector2(in.x, in.y);
}

void ConstructorVector2Floats(float x, float y, Vector2* other)
{
	new(other) Vector2(x, y);
}

void DestructVector2(Vector2* other)
{
	other->~Vector2();
}

static Vector2& Vector2AddAssignVector2(const Vector2& other, Vector2* self)
{
	return *self = *self + other;
}

void ScriptInterface::RegisterVector2()
{
	scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructorVector2), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2 &in)", asFUNCTION(CopyConstructorVector2), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructorVector2Floats), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVector2), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector2", "Vector2 &opAddAssign(const Vector2 &in)", asFUNCTION(Vector2AddAssignVector2), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2 &in)", asMETHODPR(Vector2, operator=, (const Vector2&), Vector2&), asCALL_THISCALL);
	scriptEngine->RegisterObjectProperty("Vector2", "float x", asOFFSET(Vector2, x));
	scriptEngine->RegisterObjectProperty("Vector2", "float y", asOFFSET(Vector2, y));
}

void ConstructorVector3(Vector3* self)
{
	new(self) Vector3(0, 0, 0);
}

void CopyConstructorVector3(const Vector3& other, Vector3* self)
{
	new(self) Vector3(other.x, other.y, other.z);
}

void ConstructorVector3Floats(float x, float y, float z, Vector3* self)
{
	new(self) Vector3(x, y, z);
}

void DestructVector3(Vector3* self)
{
	self->~Vector3();
}

static Vector3& Vector3Assignment(const Vector3& other, Vector3* self)
{
	return *self = other;
}

static Vector3 Vector3AddVector3(const Vector3& other, Vector3* self)
{
	return *self + other;
}

static Vector3& Vector3AddAssignVector3(const Vector3& other, Vector3* self)
{
	return *self = *self + other;
}

static Vector3& Vector3SubAssignVector3(const Vector3& other, Vector3* self)
{
	return *self = *self - other;
}

static Vector3& Vector3MulAssignVector3(const Vector3& other, Vector3* self)
{
	return *self = *self * other;
}

static Vector3& Vector3MulAssignFloat(float value, Vector3* self)
{
	return *self = *self * value;
}

static Vector3 Vector3MulVector3(const Vector3& other, Vector3* self)
{
	return *self * other;
}

static Vector3 Vector3MulFloat(float value, Vector3* self)
{
	return *self * value;
}

void ScriptInterface::RegisterVector3()
{
	scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructorVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in)", asFUNCTION(CopyConstructorVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructorVector3Floats), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Vector3 &in)", asFUNCTION(Vector3Assignment), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3 &in)", asFUNCTION(Vector3AddVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 &opAddAssign(const Vector3 &in)", asFUNCTION(Vector3AddAssignVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 &opSubAssign(const Vector3 &in)", asFUNCTION(Vector3SubAssignVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 &opMulAssign(const Vector3 &in)", asFUNCTION(Vector3MulAssignVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 &opMulAssign(float)", asFUNCTION(Vector3MulAssignFloat), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3 &in)", asFUNCTION(Vector3MulVector3), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul(float)", asFUNCTION(Vector3MulFloat), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul_r(float)", asFUNCTION(Vector3MulFloat), asCALL_CDECL_OBJLAST);
	scriptEngine->RegisterObjectProperty("Vector3", "float x", asOFFSET(Vector3, x));
	scriptEngine->RegisterObjectProperty("Vector3", "float y", asOFFSET(Vector3, y));
	scriptEngine->RegisterObjectProperty("Vector3", "float z", asOFFSET(Vector3, z));
}
