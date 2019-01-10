#include "stdafx.h"
#include "Renderer.h"
#include "../D3D11/Pipeline.h"
#include "../../Scene/Scene.h"
#include "../../Scene/GameObject.h"
#include "../../Scene/Component/Camera.h"
#include "../../Scene/Component/Transform.h"
#include "../../Scene/Component/Renderable.h"

Renderer::Renderer(Context * context)
	: ISubsystem(context)
	, graphics(nullptr)
	, mainCamera(nullptr)
	, editorCamera(nullptr)
	, sceneCamera(nullptr)
	, renderTexture(nullptr)
	, cameraBuffer(nullptr)
	, transformBuffer(nullptr)
	, pipeline(nullptr)
{

}

Renderer::~Renderer()
{
	Clear();
	SAFE_DELETE(editorCamera);
	SAFE_DELETE(pipeline);
	SAFE_DELETE(transformBuffer);
	SAFE_DELETE(cameraBuffer);
	SAFE_DELETE(renderTexture);
}

void Renderer::SetRenderables(Scene * scene)
{
	Clear();

	auto objects = scene->GetObjects();
	for (const auto& object : objects)
	{
		auto renderable = object->GetComponent<Renderable>();
		auto camera = object->GetComponent<Camera>();

		if (renderable)
			renderables[RenderableType::OpaqueObject].emplace_back(object);
		else if (camera)
		{
			renderables[RenderableType::Camera].emplace_back(object);
			sceneCamera = camera;
		}
	}
}

const bool Renderer::Initialize()
{
	graphics = context->GetSubsystem<Graphics>();

	editorCamera = new Camera(context);

	renderTexture = new RenderTexture(context);
	renderTexture->Create
	(
		static_cast<uint>(Settings::Get()->GetWidth()),
		static_cast<uint>(Settings::Get()->GetHeight())
	);

	cameraBuffer = new ConstantBuffer(context);
	cameraBuffer->Create<CameraData>(ShaderType::VS, 0);

	transformBuffer = new ConstantBuffer(context);
	transformBuffer->Create<TransformData>(ShaderType::VS, 1);

	pipeline = new Pipeline(context);

	return true;
}

void Renderer::Render()
{
	renderTexture->Clear();
	renderTexture->SetRenderTarget();
	
	mainCamera = Engine::IsOnEngineFlags(EngineFlags_Game) ? sceneCamera : editorCamera;
	mainCamera->EditorCameraUpdate(); //에디터모드일때
	
	if (mainCamera)
	{
		if (renderables.empty())
			return;

		auto cameraData = static_cast<CameraData*>(cameraBuffer->Map());
		cameraData->View = mainCamera->GetViewMatrix();
		cameraData->Proj = mainCamera->GetProjMatrix();
		cameraBuffer->Unmap();
		pipeline->SetConstantBuffer(cameraBuffer);

		PassPreRender();
	}
}

void Renderer::Clear()
{
	renderables.clear();
	mainCamera = nullptr;
}

void Renderer::PassPreRender()
{
	for (const auto& object : renderables[RenderableType::OpaqueObject])
	{
		auto renderable = object->GetComponent<Renderable>();
		auto transform = object->GetComponent<Transform>();
		auto material = renderable->GetMaterial();

		if (!material)
			continue;

		auto transformData = static_cast<TransformData*>(transformBuffer->Map());
		transformData->World = transform->GetWorldMatrix();
		transformBuffer->Unmap();

		pipeline->SetConstantBuffer(transformBuffer);
		pipeline->SetVertexBuffer(renderable->GetVertexBuffer());
		pipeline->SetIndexBuffer(renderable->GetIndexBuffer());
		pipeline->SetPrimitiveTopology(renderable->GetPrimitiveTopology());
		pipeline->SetInputLayout(material->GetShader()->GetInputLayout());
		pipeline->SetVertexShader(material->GetShader()->GetVertexShader());
		pipeline->SetPixelShader(material->GetShader()->GetPixelShader());
		pipeline->SetTexture(ShaderType::PS, material->GetDiffuseTexture());
		pipeline->BindPipeline();

		graphics->GetDeviceContext()->DrawIndexed
		(
			renderable->GetMesh().IndicesCount(),
			0,
			0
		);
	}
}
