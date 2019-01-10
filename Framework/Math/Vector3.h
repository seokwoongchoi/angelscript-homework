#pragma once

class Vector3 final
{
public:
	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 Right;
	static const Vector3 Left;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Forward;
	static const Vector3 Back;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;

public:
	static const float Distance(const Vector3& lhs, const Vector3& rhs);
	static const float DistanceSq(const Vector3& lhs, const Vector3& rhs);
	static const float Dot(const Vector3& lhs, const Vector3& rhs);

	static const Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	static const Vector3 Normalize(const Vector3& rhs);
	static const Vector3 Transform(const Vector3& lhs, const class Matrix& rhs);
	static const Vector3 TransformCoord(const Vector3& lhs, const class Matrix& rhs);
	static const Vector3 TransformNormal(const Vector3& lhs, const class Matrix& rhs);
	static const Vector3 Lerp(const Vector3& lhs, const Vector3& rhs, const float& factor);

public:
	Vector3() 
		: x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(const float& x, const float& y, const float& z)
		: x(x), y(y), z(z) {}
	Vector3(const Vector3& rhs)
		: x(rhs.x), y(rhs.y), z(rhs.z) {}
	Vector3(const float& f)
		: x(f), y(f), z(f) {}
	~Vector3() {}

	const float Length() const { return sqrt(x * x + y * y + z * z); }
	const float LengthSq() const { return x * x + y * y + z * z; }
	const float Volume() const { return x * y * z; }
	const float Dot(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

	const Vector3 Cross(const Vector3& rhs) const { return Cross(*this, rhs); }
	const Vector3 Absolute() const { return Vector3(fabs(x), fabs(y), fabs(z)); }
	const Vector3 Normalize() const;
	void Normalize();

	operator float*() { return static_cast<float*>(&x); }
	operator const float*() const { return static_cast<const float*>(&x); }

	const Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	const Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	const Vector3 operator*(const Vector3& rhs) const { return Vector3(x * rhs.x, y * rhs.y, z * rhs.z); }
	const Vector3 operator/(const Vector3& rhs) const { return Vector3(x / rhs.x, y / rhs.y, z / rhs.z); }

	const Vector3 operator+(const float& f) const { return Vector3(x + f, y + f, z + f); }
	const Vector3 operator-(const float& f) const { return Vector3(x - f, y - f, z - f); }
	const Vector3 operator*(const float& f) const { return Vector3(x * f, y * f, z * f); }
	const Vector3 operator/(const float& f) const { return Vector3(x / f, y / f, z / f); }

	void operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
	void operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
	void operator*=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; }
	void operator/=(const Vector3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; }

	void operator+=(const float& f) { x += f; y += f; z += f; }
	void operator-=(const float& f) { x -= f; y -= f; z -= f; }
	void operator*=(const float& f) { x *= f; y *= f; z *= f; }
	void operator/=(const float& f) { x /= f; y /= f; z /= f; }

	const bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	const bool operator!=(const Vector3& rhs) const { return !(*this == rhs); }

public:
	float x;
	float y;
	float z;
};