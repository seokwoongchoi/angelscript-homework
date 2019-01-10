#include "stdafx.h"
#include "Vector3.h"
#include "Matrix.h"

const Vector3 Vector3::Zero(0.0f);
const Vector3 Vector3::One(1.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Back(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Infinity(numeric_limits<float>::infinity());
const Vector3 Vector3::NegInfinity(-numeric_limits<float>::infinity());

const float Vector3::Distance(const Vector3 & lhs, const Vector3 & rhs)
{
	float num1 = lhs.x - rhs.x;
	float num2 = lhs.y - rhs.y;
	float num3 = lhs.z - rhs.z;

	return sqrt(num1 * num1 + num2 * num2 + num3 * num3);
}

const float Vector3::DistanceSq(const Vector3 & lhs, const Vector3 & rhs)
{
	float num1 = lhs.x - rhs.x;
	float num2 = lhs.y - rhs.y;
	float num3 = lhs.z - rhs.z;

	return num1 * num1 + num2 * num2 + num3 * num3;
}

const float Vector3::Dot(const Vector3 & lhs, const Vector3 & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

const Vector3 Vector3::Cross(const Vector3 & lhs, const Vector3 & rhs)
{
	float num1 = lhs.y * rhs.z - lhs.z * rhs.y;
	float num2 = lhs.z * rhs.x - lhs.x * rhs.z;
	float num3 = lhs.x * rhs.y - lhs.y * rhs.x;

	return Vector3(num1, num2, num3);
}

const Vector3 Vector3::Normalize(const Vector3 & rhs)
{
	return rhs.Normalize();
}

const Vector3 Vector3::Transform(const Vector3 & lhs, const Matrix & rhs)
{
	float num1 = lhs.x * rhs._11 + lhs.y * rhs._21 + lhs.z * rhs._31 + rhs._41;
	float num2 = lhs.x * rhs._12 + lhs.y * rhs._22 + lhs.z * rhs._32 + rhs._42;
	float num3 = lhs.x * rhs._13 + lhs.y * rhs._23 + lhs.z * rhs._33 + rhs._43;
	float num4 = lhs.x * rhs._14 + lhs.y * rhs._24 + lhs.z * rhs._34 + rhs._44;

	return Vector3(num1, num2, num3);
}

const Vector3 Vector3::TransformCoord(const Vector3 & lhs, const Matrix & rhs)
{
	float num1 = lhs.x * rhs._11 + lhs.y * rhs._21 + lhs.z * rhs._31 + rhs._41;
	float num2 = lhs.x * rhs._12 + lhs.y * rhs._22 + lhs.z * rhs._32 + rhs._42;
	float num3 = lhs.x * rhs._13 + lhs.y * rhs._23 + lhs.z * rhs._33 + rhs._43;
	float num4 = lhs.x * rhs._14 + lhs.y * rhs._24 + lhs.z * rhs._34 + rhs._44;

	float factor = 1.0f / num4;

	return Vector3(num1 * factor, num2 * factor, num3 * factor);
}

const Vector3 Vector3::TransformNormal(const Vector3 & lhs, const Matrix & rhs)
{
	float num1 = lhs.x * rhs._11 + lhs.y * rhs._21 + lhs.z * rhs._31;
	float num2 = lhs.x * rhs._12 + lhs.y * rhs._22 + lhs.z * rhs._32;
	float num3 = lhs.x * rhs._13 + lhs.y * rhs._23 + lhs.z * rhs._33;
	float num4 = lhs.x * rhs._14 + lhs.y * rhs._24 + lhs.z * rhs._34;

	return Vector3(num1, num2, num3);
}

const Vector3 Vector3::Lerp(const Vector3 & lhs, const Vector3 & rhs, const float & factor)
{
	float num1 = lhs.x + (rhs.x - lhs.x) * factor;
	float num2 = lhs.y + (rhs.y - lhs.y) * factor;
	float num3 = lhs.z + (rhs.z - lhs.z) * factor;

	return Vector3(num1, num2, num3);
}

const Vector3 Vector3::Normalize() const
{
	float factor = Length();
	factor = 1.0f / factor;

	return Vector3(x * factor, y * factor, z * factor);
}

void Vector3::Normalize()
{
	float factor = Length();
	factor = 1.0f / factor;

	x *= factor;
	y *= factor;
	z *= factor;
}
