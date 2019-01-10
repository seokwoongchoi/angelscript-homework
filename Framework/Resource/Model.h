#pragma once
#include "IResource.h"

class Model : public IResource
{
public:
	Model(class Context* context);
	virtual ~Model();

	void Update();
	void Render();

private:
	class Mesh<VertexTexture> mesh;
	class VertexBuffer* vertexBuffer;
	class IndexBuffer* indexBuffer;
	class Shader* shader;
	class Texture* texture;
	class Animator* animator;

	class ConstantBuffer* spriteBuffer;
};