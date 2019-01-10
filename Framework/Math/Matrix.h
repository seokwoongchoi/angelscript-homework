#pragma once

class Matrix final
{
public:
	static const Matrix Identity;

public:
	static const Matrix Scaling(const float& s) { return Scaling(s, s, s); }
	static const Matrix Scaling(const class Vector3& s);
	static const Matrix Scaling(const float& x, const float& y, const float& z);

	static const Matrix RotationX(const float& radian);
	static const Matrix RotationY(const float& radian);
	static const Matrix RotationZ(const float& radian);
	static const Matrix RotationYawPitchRoll(const float& yaw, const float& pitch, const float& roll);
	static const Matrix RotationYawPitchRoll(const class Vector3& rotation);

	static const Matrix Translation(const float& p) { return Translation(p, p, p); }
	static const Matrix Translation(const class Vector3& p);
	static const Matrix Translation(const float& x, const float& y, const float& z);

	static const Matrix LookAtLH
	(
		const class Vector3& position, 
		const class Vector3& target, 
		const class Vector3& up
	);
	static const Matrix OrthoLH
	(
		const float& w,
		const float& h,
		const float& zn,
		const float& zf
	);
	static const Matrix OrthoOffCenterLH
	(
		const float& l,
		const float& r,
		const float& b,
		const float& t,
		const float& zn,
		const float& zf
	);

	static Matrix Inverse(const Matrix& m);
	static Matrix Transpose(const Matrix& m);

public:
	Matrix();
	Matrix
	(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44
	);
	~Matrix() {}

	const Vector3 GetScale();
	const Vector3 GetRotation();
	const Vector3 GetTranslation();

	const Matrix Inverse() const { return Inverse(*this); }
	const Matrix Transpose() const { return Transpose(*this); }
	void Transpose() { *this = Transpose(*this); }

	void Decompose
	(
		Vector3& scale,
		Vector3& rotation,
		Vector3& translation
	);
	void SetIdentity();

	const float* Data() const { return &_11; }

	operator float*() { return static_cast<float*>(&_11); }
	operator const float*() const { return static_cast<const float*>(&_11); }

	const Matrix operator*(const Matrix& m) const;
	const bool operator==(const Matrix& m) const;
	const bool operator!=(const Matrix& m) const { return !(*this == m); }

public:
	float _11, _21, _31, _41;
	float _12, _22, _32, _42;
	float _13, _23, _33, _43;
	float _14, _24, _34, _44;
};
