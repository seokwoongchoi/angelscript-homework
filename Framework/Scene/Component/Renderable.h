#pragma once
#include "IComponent.h"

enum class RenderType : uint
{
	Draw,
	DrawIndexed,
	Instancing,
};

enum class ModelType : uint
{
	Quad,
	ScreenQuad,
	Circle,
	Custom
};

class Renderable : public IComponent
{
public:
	Renderable
	(
		class Context* context,
		class GameObject* object,
		class Transform* transform
	);
	virtual ~Renderable();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;
	void OnSave()override;
	


	class Material* GetMaterial() const { return material; }
	const class Mesh<VertexTexture>& GetMesh() const { return mesh; }
	class VertexBuffer* GetVertexBuffer() const { return vertexBuffer; }
	class IndexBuffer* GetIndexBuffer() const { return indexBuffer; }
	class PrimitiveTopology* GetPrimitiveTopology() const { return topology; }
	const RenderType& GetRenderType() const { return renderType; }
	const ModelType& GetModelType() const { return modelType; }
	const BoundBox& GetBoundBox() const { return boundBox; }
	const bool& IsAnimated() const { return bAnimated; }

	void SetMaterial(class Material* material) { this->material = material; }
	void SetMesh(const class Mesh<VertexTexture>& mesh) { this->mesh = mesh; }
	void SetVertexBuffer(class VertexBuffer* vertexBuffer) { this->vertexBuffer = vertexBuffer; }
	void SetIndexBuffer(class IndexBuffer* indexBuffer) { this->indexBuffer = indexBuffer; }
	void SetPrimitiveTopology(class PrimitiveTopology* topology) { this->topology = topology; }
	void SetRenderType(const RenderType& renderType) { this->renderType = renderType; }
	void SetModelType(const ModelType& modelType);

private:
	void SetGeometry(const ModelType& type);

private:
	class Material* material;
	class SceneManager* sceneManager;
	class Mesh<VertexTexture> mesh;
	class VertexBuffer* vertexBuffer;
	class IndexBuffer* indexBuffer;
	class PrimitiveTopology* topology;
	RenderType renderType;
	ModelType modelType;
	BoundBox boundBox;
	bool bAnimated;
};