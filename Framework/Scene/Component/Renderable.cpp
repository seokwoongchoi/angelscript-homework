#include "stdafx.h"
#include "Renderable.h"
#include "Transform.h"
#include "Framework/Scene/GameObject.h"
#include "Framework/Scene/Scene.h"

Renderable::Renderable(Context * context, GameObject * object, Transform * transform)
	: IComponent(context, object, transform)
	, material(nullptr)
	, vertexBuffer(nullptr)
	, indexBuffer(nullptr)
	, topology(nullptr)
	, renderType(RenderType::DrawIndexed)
	, modelType(ModelType::Custom)
{
	material = new Material(context);
	material->SetShader("Default.hlsl");
	sceneManager = context->GetSubsystem<SceneManager>();
	topology = new PrimitiveTopology(context);
}

Renderable::~Renderable()
{
	SAFE_DELETE(topology);
	SAFE_DELETE(material);
}

void Renderable::OnInitialize()
{
}

void Renderable::OnStart()
{
}

void Renderable::OnUpdate()
{
}

void Renderable::OnStop()
{
}

void Renderable::OnDestroy()
{
}

void Renderable::OnSave()
{
}




void Renderable::SetModelType(const ModelType & modelType)
{
	this->modelType = modelType;
	SetGeometry(modelType);
}

void Renderable::SetGeometry(const ModelType & type)
{
	vertexBuffer = new VertexBuffer(context);
	indexBuffer = new IndexBuffer(context);

	switch (type)
	{
	case ModelType::Quad: GeometryUtility::CreateQuad(&mesh); break;
	case ModelType::ScreenQuad: GeometryUtility::CreateScreenQuad(&mesh); break;
	case ModelType::Circle: break;
	}

	boundBox = BoundBox(mesh.AppendVertices());
	boundBox.Transformed(transform->GetWorldMatrix());

	vertexBuffer->Create<VertexTexture>(mesh.AppendVertices());
	indexBuffer->Create(mesh.AppendIndices());
}
