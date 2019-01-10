#include "stdafx.h"
#include "GeometryUtility.h"

void GeometryUtility::CreateQuad(Mesh<Vertex>* mesh)
{
	mesh->AddVertex(Vertex(-0.5f, -0.5f, 0.0f)); //0
	mesh->AddVertex(Vertex(-0.5f, +0.5f, 0.0f)); //1
	mesh->AddVertex(Vertex(+0.5f, -0.5f, 0.0f)); //2
	mesh->AddVertex(Vertex(+0.5f, +0.5f, 0.0f)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}

void GeometryUtility::CreateQuad(Mesh<VertexColor>* mesh)
{
	mesh->AddVertex(VertexColor(-0.5f, -0.5f, 0.0f, 0, 0, 0, 1)); //0
	mesh->AddVertex(VertexColor(-0.5f, +0.5f, 0.0f, 0, 0, 0, 1)); //1
	mesh->AddVertex(VertexColor(+0.5f, -0.5f, 0.0f, 0, 0, 0, 1)); //2
	mesh->AddVertex(VertexColor(+0.5f, +0.5f, 0.0f, 0, 0, 0, 1)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}

void GeometryUtility::CreateQuad(Mesh<VertexTexture>* mesh)
{
	mesh->AddVertex(VertexTexture(-0.5f, -0.5f, 0.0f, 0, 1)); //0
	mesh->AddVertex(VertexTexture(-0.5f, +0.5f, 0.0f, 0, 0)); //1
	mesh->AddVertex(VertexTexture(+0.5f, -0.5f, 0.0f, 1, 1)); //2
	mesh->AddVertex(VertexTexture(+0.5f, +0.5f, 0.0f, 1, 0)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}

void GeometryUtility::CreateScreenQuad(Mesh<Vertex>* mesh)
{
	float w = Settings::Get()->GetWidth() * 0.5f;
	float h = Settings::Get()->GetHeight() * 0.5f;

	mesh->AddVertex(Vertex(-w, -h, 0.0f)); //0
	mesh->AddVertex(Vertex(-w, +h, 0.0f)); //1
	mesh->AddVertex(Vertex(+w, -h, 0.0f)); //2
	mesh->AddVertex(Vertex(+w, +h, 0.0f)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}

void GeometryUtility::CreateScreenQuad(Mesh<VertexTexture>* mesh)
{
	float w = Settings::Get()->GetWidth() * 0.5f;
	float h = Settings::Get()->GetHeight() * 0.5f;

	mesh->AddVertex(VertexTexture(-w, -h, 0.0f, 0, 1)); //0
	mesh->AddVertex(VertexTexture(-w, +h, 0.0f, 0, 0)); //1
	mesh->AddVertex(VertexTexture(+w, -h, 0.0f, 1, 1)); //2
	mesh->AddVertex(VertexTexture(+w, +h, 0.0f, 1, 0)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}