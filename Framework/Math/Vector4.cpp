#include "stdafx.h"
#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4(Vector3 & rhs)
	: x(rhs.x)
	, y(rhs.y)
	, z(rhs.z)
	, w(0.0f)
{
}

Vector4::Vector4(Vector3 & rhs, const float & w)
	: x(rhs.x)
	, y(rhs.y)
	, z(rhs.z)
	, w(w)
{
}
