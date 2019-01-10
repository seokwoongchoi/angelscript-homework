#pragma once

class Vector2 final
{
public:
	static const Vector2 Zero;
	static const Vector2 One;

public:
	Vector2() 
		: x(0.0f), y(0.0f) {}
	Vector2(const float& x, const float& y)
		: x(x), y(y) {}
	Vector2(const Vector2& v)
		: x(v.x), y(v.y) {}
	Vector2(const float& f)
		: x(f), y(f) {}
	~Vector2() {}

	operator float*() { return static_cast<float*>(&x); }
	operator const float*() const { return static_cast<const float*>(&x); }

	const Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	const Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	const Vector2 operator*(const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
	const Vector2 operator/(const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

	const Vector2 operator+(const float& f) const { return Vector2(x + f, y + f); }
	const Vector2 operator-(const float& f) const { return Vector2(x - f, y - f); }
	const Vector2 operator*(const float& f) const { return Vector2(x * f, y * f); }
	const Vector2 operator/(const float& f) const { return Vector2(x / f, y / f); }

	void operator+=(const Vector2& v) { x += v.x; y += v.y; }
	void operator-=(const Vector2& v) { x -= v.x; y -= v.y; }
	void operator*=(const Vector2& v) { x *= v.x; y *= v.y; }
	void operator/=(const Vector2& v) { x /= v.x; y /= v.y; }

	void operator+=(const float& f) { x += f; y += f; }
	void operator-=(const float& f) { x -= f; y -= f; }
	void operator*=(const float& f) { x *= f; y *= f; }
	void operator/=(const float& f) { x /= f; y /= f; }

	const bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
	const bool operator!=(const Vector2& v) const { return x != v.x || y != v.y; }

public:
	float x;
	float y;
};