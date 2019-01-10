#include "stdafx.h"
#include "Effect.h"
#include "../Scene/Component/Animator.h"

Effect::Effect(Context * context)
	: IResource(context)
	, texture(nullptr)
	, bExist(false)
{
	//정점 정보 만들기
	GeometryUtility::CreateQuad(&mesh);

	//버텍스 버퍼 만들기
	vertexBuffer = new VertexBuffer(context->GetSubsystem<Graphics>());
	vertexBuffer->Create<VertexTexture>(mesh.AppendVertices());

	//인덱스 버퍼 만들기
	indexBuffer = new IndexBuffer(context->GetSubsystem<Graphics>());
	indexBuffer->Create(mesh.AppendIndices());

	//셰이더 만들기
	shader = resourceManager->Load<Shader>("Sprite.hlsl");

	spriteBuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
	spriteBuffer->Create<SpriteData>();

	transformBuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
	transformBuffer->Create<TransformData>();

	animator = new Animator(context);
	transform = new Transform(context);
}

Effect::~Effect()
{
	SAFE_DELETE(transformBuffer);
	SAFE_DELETE(transform);
	SAFE_DELETE(animator);
	SAFE_DELETE(spriteBuffer);
	SAFE_DELETE(indexBuffer);
	SAFE_DELETE(vertexBuffer);
}

void Effect::SetTexture(const string & filePath)
{
	texture = resourceManager->Load<Texture>(filePath);
}

void Effect::SetAnimation(const string & filePath)
{
	animator->AddAnimation(filePath);
	animator->SetCurrentAnimation("Idle");
	animator->Play();
}

void Effect::Update()
{
	if (bExist)
	{
		animator->Update();

		auto curKeyframe = animator->GetCurrentKeyframe();

		auto spriteData = static_cast<SpriteData*>(spriteBuffer->Map());
		spriteData->TextureSize = curKeyframe.texture->GetSize();
		spriteData->SpriteOffset = curKeyframe.offset;
		spriteData->SpriteSize = curKeyframe.size;
		spriteBuffer->Unmap();

		auto transformData = static_cast<TransformData*>(transformBuffer->Map());
		D3DXMatrixTranspose(&transformData->World, &transform->GetWorldMatrix());
		transformBuffer->Unmap();

		if (!animator->IsPlaying())
			bExist = false;
	}
}

void Effect::Render()
{
	if (bExist)
	{
		vertexBuffer->BindPipeline();
		indexBuffer->BindPipeline();

		shader->BindPipeline();

		transformBuffer->SetVS(1);
		spriteBuffer->SetVS(2);
		texture->SetPS(0);

		auto graphics = context->GetSubsystem<Graphics>();
		graphics->GetDeviceContext()->IASetPrimitiveTopology
		(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);

		//Draw Call
		graphics->GetDeviceContext()->DrawIndexed
		(
			mesh.IndicesCount(),
			0,
			0
		);
	}
}


void Effect::SaveToFile(const string & saveFilePath)
{
}

void Effect::LoadFromFile(const string & loadFilePath)
{
}
