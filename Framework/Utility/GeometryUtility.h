#pragma once

class GeometryUtility
{
public:
	static void CreateQuad(class Mesh<Vertex>* mesh);
	static void CreateQuad(class Mesh<VertexColor>* mesh);
	static void CreateQuad(class Mesh<VertexTexture>* mesh);

	static void CreateScreenQuad(class Mesh<Vertex>* mesh);
	static void CreateScreenQuad(class Mesh<VertexTexture>* mesh);
};