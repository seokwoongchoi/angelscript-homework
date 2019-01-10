#pragma once

class Vector4 final
{
public:
	Vector4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(const float& x, const float& y, const float& z, const float& w)
		: x(x), y(y), z(z), w(w) {}
	Vector4(const Vector4& rhs)
		: x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
	Vector4(const float& f)
		: x(f), y(f), z(f), w(w) {}
	Vector4(class Vector3& rhs);
	Vector4(class Vector3& rhs, const float& w);
	~Vector4() {}

	const float* Data() const { return &x; }

	operator float*() { return static_cast<float*>(&x); }
	operator const float*() const { return static_cast<const float*>(&x); }

	const bool operator==(const Vector4& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
	const bool operator!=(const Vector4& rhs) const { return !(*this == rhs); }

public:
	float x;
	float y;
	float z;
	float w;
};