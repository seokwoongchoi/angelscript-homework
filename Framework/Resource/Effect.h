#pragma once
#include "IResource.h"
#include "../Scene/Component/Transform.h"

class Effect : public IResource
{
public:
	Effect(class Context* context);
	virtual ~Effect();

	const bool& IsExist() const { return bExist; }

	void SetIsExist(const bool& bExist) { this->bExist = bExist; }
	void SetPosition(const Vector3& position) { transform->SetPosition(position); }
	void SetScale(const Vector3& scale) { transform->SetScale(scale); }
	void SetTexture(const string& filePath);
	void SetAnimation(const string& filePath);

	void Update();
	void Render();

	virtual void SaveToFile(const string& saveFilePath) override;
	virtual void LoadFromFile(const string& loadFilePath) override;

private:
	class Mesh<VertexTexture> mesh;
	class VertexBuffer* vertexBuffer;
	class IndexBuffer* indexBuffer;
	class Shader* shader;
	class Texture* texture;
	class Animator* animator;
	class Transform* transform;
	class ConstantBuffer* spriteBuffer;
	class ConstantBuffer* transformBuffer;
	bool bExist;
};