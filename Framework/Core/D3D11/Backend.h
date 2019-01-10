#pragma once
#include "stdafx.h"

enum class ShaderType : uint
{
	VS, PS, GS, CS
};

struct CameraData
{
	Matrix View;
	Matrix Proj;
};

struct TransformData
{
	Matrix World;
};

struct SpriteData
{
	Vector2 TextureSize;
	Vector2 SpriteOffset;
	Vector2 SpriteSize;
	float Padding[2];
};