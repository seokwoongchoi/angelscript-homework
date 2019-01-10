#pragma once

struct Vertex
{
	Vertex() 
		: Position(0, 0, 0) 
	{}
	Vertex(const Vector3& Position)
		:Position(Position)
	{}
	Vertex(const float& x, const float& y, const float& z)
		: Position(x, y, z)
	{}

	Vector3 Position;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 1;
};

struct VertexColor
{
	VertexColor()
		: Position(0, 0, 0)
		, Color(0, 0, 0, 1)
	{}
	VertexColor(const Vector3& Position, const D3DXCOLOR& Color)
		: Position(Position)
		, Color(Color)
	{}
	VertexColor
	(
		const float& x, 
		const float& y, 
		const float& z,
		const float& r,
		const float& g,
		const float& b,
		const float& a
	)
		: Position(x, y, z)
		, Color(r, g, b, a)
	{}

	Vector3 Position;
	D3DXCOLOR Color;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 2;
};

struct VertexTexture
{
	VertexTexture()
		: Position(0, 0, 0)
		, Uv(0, 0)
	{}
	VertexTexture(const Vector3& Position, const Vector2& Uv)
		: Position(Position)
		, Uv(Uv)
	{}
	VertexTexture
	(
		const float& x,
		const float& y,
		const float& z,
		const float& u,
		const float& v
	)
		: Position(x, y, z)
		, Uv(u, v)
	{}

	Vector3 Position;
	Vector2 Uv;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 2;
};