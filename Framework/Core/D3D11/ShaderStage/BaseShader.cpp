#include "stdafx.h"
#include "BaseShader.h"

BaseShader::BaseShader(Context * context)
	: shaderFilePath("")
	, functionName("")
{
	graphics = context->GetSubsystem<Graphics>();
}

BaseShader::~BaseShader()
{
}

bool BaseShader::CheckShaderError(const HRESULT & hr, ID3D10Blob * error)
{
	if (FAILED(hr))
	{
		if (error != nullptr)
		{
			string str = reinterpret_cast<const char*>(error->GetBufferPointer());
			MessageBoxA
			(
				Settings::Get()->GetWindowHandle(),
				str.c_str(),
				"Shader Error!!!",
				MB_OK
			);
		}
		return false;
	}

	return true;
}
