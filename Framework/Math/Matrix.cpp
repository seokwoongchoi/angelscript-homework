#include "stdafx.h"
#include "Matrix.h"
#include "Vector3.h"

const Matrix Matrix::Identity
(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);

const Matrix Matrix::Scaling(const Vector3 & s)
{
	return Scaling(s.x, s.y, s.z);
}

const Matrix Matrix::Scaling(const float & x, const float & y, const float & z)
{
	return Matrix
	(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	);
}

const Matrix Matrix::RotationX(const float & radian)
{
	float s = sinf(radian);
	float c = cosf(radian);

	return Matrix
	(
		1, 0, 0, 0,
		0, c, s, 0,
		0, -s, c, 0,
		0, 0, 0, 1
	);
}

const Matrix Matrix::RotationY(const float & radian)
{
	float s = sinf(radian);
	float c = cosf(radian);

	return Matrix
	(
		c, 0, -s, 0,
		0, 1, 0, 0,
		s, 0, c, 0,
		0, 0, 0, 1
	);
}

const Matrix Matrix::RotationZ(const float & radian)
{
	float s = sinf(radian);
	float c = cosf(radian);

	return Matrix
	(
		c, s, 0, 0,
		-s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

const Matrix Matrix::RotationYawPitchRoll(const float & yaw, const float & pitch, const float & roll)
{
	float sa = sinf(roll), sb = sinf(pitch), sc = sinf(yaw);
	float ca = cosf(roll), cb = cosf(pitch), cc = cosf(yaw);

	return Matrix
	(
		(ca * cc + sa * sb * sc), (-sa * cc + ca * sb * sc), (cb * sc), 0,
		(sa * cb), (ca * cb), -sb, 0,
		(-ca * sc + sa * sb * cc), (sa * sc + ca * sb * cc), (cb * cc), 0,
		0, 0, 0, 1
	);
}

const Matrix Matrix::RotationYawPitchRoll(const Vector3 & rotation)
{
	return RotationYawPitchRoll(rotation.y, rotation.x, rotation.z);
}

const Matrix Matrix::Translation(const Vector3 & p)
{
	return Translation(p.x, p.y, p.z);
}

const Matrix Matrix::Translation(const float & x, const float & y, const float & z)
{
	return Matrix
	(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	);
}

const Matrix Matrix::LookAtLH(const Vector3 & position, const Vector3 & target, const Vector3 & up)
{
	Vector3 zAxis = Vector3::Normalize(target - position);
	Vector3 xAxis = Vector3::Normalize(Vector3::Cross(up, zAxis));
	Vector3 yAxis = Vector3::Normalize(Vector3::Cross(zAxis, xAxis));

	return Matrix
	(
		xAxis.x, yAxis.x, zAxis.x, 0,
		xAxis.y, yAxis.y, zAxis.y, 0,
		xAxis.z, yAxis.z, zAxis.z, 0,
		-Vector3::Dot(xAxis, position), -Vector3::Dot(yAxis, position), -Vector3::Dot(zAxis, position), 1
	);
}

const Matrix Matrix::OrthoLH(const float & w, const float & h, const float & zn, const float & zf)
{
	return Matrix
	(
		2 / w, 0, 0, 0,
		0, 2 / h, 0, 0,
		0, 0, 1 / (zf - zn), 0,
		0, 0, zn / (zn - zf), 1
	);
}

const Matrix Matrix::OrthoOffCenterLH(const float & l, const float & r, const float & b, const float & t, const float & zn, const float & zf)
{
	return Matrix
	(
		2 / (r - l), 0, 0, 0,
		0, 2 / (t - b), 0, 0,
		0, 0, 1 / (zf - zn), 0,
		(l + r) / (l - r), (t + b) / (b - t), zn / (zn - zf), 1
	);
}

Matrix Matrix::Inverse(const Matrix & m)
{
	float v0 = m._31 * m._42 - m._32 * m._41;
	float v1 = m._31 * m._43 - m._33 * m._41;
	float v2 = m._31 * m._44 - m._34 * m._41;
	float v3 = m._32 * m._43 - m._33 * m._42;
	float v4 = m._32 * m._44 - m._34 * m._42;
	float v5 = m._33 * m._44 - m._34 * m._43;

	float i00 = (v5 * m._22 - v4 * m._23 + v3 * m._24);
	float i10 = -(v5 * m._21 - v2 * m._23 + v1 * m._24);
	float i20 = (v4 * m._21 - v2 * m._22 + v0 * m._24);
	float i30 = -(v3 * m._21 - v1 * m._22 + v0 * m._23);

	float invDet = 1.0f / (i00 * m._11 + i10 * m._12 + i20 * m._13 + i30 * m._14);

	i00 *= invDet;
	i10 *= invDet;
	i20 *= invDet;
	i30 *= invDet;

	float i01 = -(v5 * m._12 - v4 * m._13 + v3 * m._14) * invDet;
	float i11 = (v5 * m._11 - v2 * m._13 + v1 * m._14) * invDet;
	float i21 = -(v4 * m._11 - v2 * m._12 + v0 * m._14) * invDet;
	float i31 = (v3 * m._11 - v1 * m._12 + v0 * m._13) * invDet;

	v0 = m._21 * m._42 - m._22 * m._41;
	v1 = m._21 * m._43 - m._23 * m._41;
	v2 = m._21 * m._44 - m._24 * m._41;
	v3 = m._22 * m._43 - m._23 * m._42;
	v4 = m._22 * m._44 - m._24 * m._42;
	v5 = m._23 * m._44 - m._24 * m._43;

	float i02 = (v5 * m._12 - v4 * m._13 + v3 * m._14) * invDet;
	float i12 = -(v5 * m._11 - v2 * m._13 + v1 * m._14) * invDet;
	float i22 = (v4 * m._11 - v2 * m._12 + v0 * m._14) * invDet;
	float i32 = -(v3 * m._11 - v1 * m._12 + v0 * m._13) * invDet;

	v0 = m._32 * m._21 - m._31 * m._22;
	v1 = m._33 * m._21 - m._31 * m._23;
	v2 = m._34 * m._21 - m._31 * m._24;
	v3 = m._33 * m._22 - m._32 * m._23;
	v4 = m._34 * m._22 - m._32 * m._24;
	v5 = m._34 * m._23 - m._33 * m._24;

	float i03 = -(v5 * m._12 - v4 * m._13 + v3 * m._14) * invDet;
	float i13 = (v5 * m._11 - v2 * m._13 + v1 * m._14) * invDet;
	float i23 = -(v4 * m._11 - v2 * m._12 + v0 * m._14) * invDet;
	float i33 = (v3 * m._11 - v1 * m._12 + v0 * m._13) * invDet;

	return Matrix
	(
		i00, i01, i02, i03,
		i10, i11, i12, i13,
		i20, i21, i22, i23,
		i30, i31, i32, i33
	);
}

Matrix Matrix::Transpose(const Matrix & m)
{
	return Matrix
	(
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44
	);
}

Matrix::Matrix()
{
	SetIdentity();
}

Matrix::Matrix(float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44)
	: _11(_11), _12(_12), _13(_13), _14(_14)
	, _21(_21), _22(_22), _23(_23), _24(_24)
	, _31(_31), _32(_32), _33(_33), _34(_34)
	, _41(_41), _42(_42), _43(_43), _44(_44)
{
}

const Vector3 Matrix::GetScale()
{
	int sx = (Math::Sign(_11 * _12 * _13) < 0) ? -1 : 1;
	int sy = (Math::Sign(_21 * _22 * _23) < 0) ? -1 : 1;
	int sz = (Math::Sign(_31 * _32 * _33) < 0) ? -1 : 1;

	return Vector3
	(
		sx * sqrt(_11 * _11 + _12 * _12 + _13 * _13),
		sy * sqrt(_21 * _21 + _22 * _22 + _23 * _23),
		sz * sqrt(_31 * _31 + _32 * _32 + _33 * _33)
	);
}

const Vector3 Matrix::GetRotation()
{
	Vector3 scale = GetScale();

	bool bCheck = false;
	bCheck |= scale.x == 0.0f;
	bCheck |= scale.y == 0.0f;
	bCheck |= scale.z == 0.0f;

	if (bCheck)
		return Vector3();

	float factorX = 1.0f / scale.x;
	float factorY = 1.0f / scale.y;
	float factorZ = 1.0f / scale.z;

	Matrix m;
	m._11 = _11 * factorX; m._12 = _12 * factorX; m._13 = _13 * factorX; m._14 = 0.0f;
	m._21 = _21 * factorY; m._22 = _22 * factorY; m._23 = _23 * factorY; m._24 = 0.0f;
	m._31 = _31 * factorZ; m._32 = _32 * factorZ; m._33 = _33 * factorZ; m._34 = 0.0f;
	m._41 = 0.0f; m._42 = 0.0f; m._43 = 0.0f; m._44 = 1.0f;

	// Y - X - Z
	return Vector3
	(
		atan2(m._31, m._33),
		atan2(-m._32, sqrt(pow(m._12, 2) + pow(m._22, 2))),
		atan2(m._12, m._22)
	);
}

const Vector3 Matrix::GetTranslation()
{
	return Vector3(_41, _42, _43);
}

void Matrix::Decompose(Vector3 & scale, Vector3 & rotation, Vector3 & translation)
{
	scale = GetScale();
	rotation = GetRotation();
	translation = GetTranslation();
}

void Matrix::SetIdentity()
{
	_11 = 1; _12 = 0; _13 = 0; _14 = 0;
	_21 = 0; _22 = 1; _23 = 0; _24 = 0;
	_31 = 0; _32 = 0; _33 = 1; _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 1;
}

const Matrix Matrix::operator*(const Matrix & m) const
{
	return Matrix
	(
		_11 * m._11 + _12 * m._21 + _13 * m._31 + _14 * m._41,
		_11 * m._12 + _12 * m._22 + _13 * m._32 + _14 * m._42,
		_11 * m._13 + _12 * m._23 + _13 * m._33 + _14 * m._43,
		_11 * m._14 + _12 * m._24 + _13 * m._34 + _14 * m._44,
		_21 * m._11 + _22 * m._21 + _23 * m._31 + _24 * m._41,
		_21 * m._12 + _22 * m._22 + _23 * m._32 + _24 * m._42,
		_21 * m._13 + _22 * m._23 + _23 * m._33 + _24 * m._43,
		_21 * m._14 + _22 * m._24 + _23 * m._34 + _24 * m._44,
		_31 * m._11 + _32 * m._21 + _33 * m._31 + _34 * m._41,
		_31 * m._12 + _32 * m._22 + _33 * m._32 + _34 * m._42,
		_31 * m._13 + _32 * m._23 + _33 * m._33 + _34 * m._43,
		_31 * m._14 + _32 * m._24 + _33 * m._34 + _34 * m._44,
		_41 * m._11 + _42 * m._21 + _43 * m._31 + _44 * m._41,
		_41 * m._12 + _42 * m._22 + _43 * m._32 + _44 * m._42,
		_41 * m._13 + _42 * m._23 + _43 * m._33 + _44 * m._43,
		_41 * m._14 + _42 * m._24 + _43 * m._34 + _44 * m._44
	);
}

const bool Matrix::operator==(const Matrix & m) const
{
	const float* lhs = Data();
	const float* rhs = m.Data();

	for (uint i = 0; i < 16; i++)
	{
		if (!Math::Equals(lhs[i], rhs[i]))
			return false;
	}

	return true;
}