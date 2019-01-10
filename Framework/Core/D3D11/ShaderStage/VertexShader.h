#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
	VertexShader(class Context* conetext);
	virtual ~VertexShader();

	ID3D10Blob* GetBlob() const { return vsBlob; }

	void Create
	(
		const string& filePath, 
		const string& functionName = "VS"
	);
	void Clear();

	void BindPipeline() override;

private:
	ID3D11VertexShader* vertexShader;
	ID3D10Blob* vsBlob;
};