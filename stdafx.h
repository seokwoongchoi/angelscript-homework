#pragma once

//Window
#include <Windows.h>
#include <assert.h>
#include <time.h>

//STL
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <fstream>
#include <algorithm>
using namespace std;

//DirectWrite
#include <d2d1_1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//Direct3D
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//FMOD
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>
#pragma comment(lib, "fmod_vc.lib")

//AngelScript
#pragma comment(lib, "angelscript.lib")

//Macro Function
#define SAFE_RELEASE(p)			{ if (p) { (p)->Release(); (p)=nullptr; } }
#define SAFE_DELETE(p)			{ if (p) { delete (p); (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] (p); (p)=nullptr; } }

//InputController
#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

//Virtual Key Code
enum VirtualKey : DWORD
{
	VK_0 = 0x30,
	VK_1 = 0x31,
	VK_2 = 0x32,
	VK_3 = 0x33,
	VK_4 = 0x34,
	VK_5 = 0x35,
	VK_6 = 0x36,
	VK_7 = 0x37,
	VK_8 = 0x38,
	VK_9 = 0x39,
	VK_A = 0x41,
	VK_B = 0x42,
	VK_C = 0x43,
	VK_D = 0x44,
	VK_E = 0x45,
	VK_F = 0x46,
	VK_G = 0x47,
	VK_H = 0x48,
	VK_I = 0x49,
	VK_J = 0x4A,
	VK_K = 0x4B,
	VK_L = 0x4C,
	VK_M = 0x4D,
	VK_N = 0x4E,
	VK_O = 0x4F,
	VK_P = 0x50,
	VK_Q = 0x51,
	VK_R = 0x52,
	VK_S = 0x53,
	VK_T = 0x54,
	VK_U = 0x55,
	VK_V = 0x56,
	VK_W = 0x57,
	VK_X = 0x58,
	VK_Y = 0x59,
	VK_Z = 0x5A,
	VK_Shift=0x10,
};

typedef unsigned int uint;

//Math
#include "./Framework/Math/Vector2.h"
#include "./Framework/Math/Vector3.h"
#include "./Framework/Math/Vector4.h"
#include "./Framework/Math/Matrix.h"

#include "./Framework/Math/Math.h"
#include "./Framework/Math/Mesh.h"
#include "./Framework/Math/BoundBox.h"

//Main System
#include "./Framework/Core/Settings.h"
#include "./Framework/Core/Context.h"

//Directx 11 Wrapper Class
#include "./Framework/Core/D3D11/Backend.h"
#include "./Framework/Core/D3D11/Vertex.h"

#include "./Framework/Core/D3D11/IAStage/VertexBuffer.h"
#include "./Framework/Core/D3D11/IAStage/IndexBuffer.h"
#include "./Framework/Core/D3D11/IAStage/InputLayout.h"
#include "./Framework/Core/D3D11/IAStage/PrimitiveTopology.h"

#include "./Framework/Core/D3D11/ShaderStage/ConstantBuffer.h"
#include "./Framework/Core/D3D11/ShaderStage/VertexShader.h"
#include "./Framework/Core/D3D11/ShaderStage/PixelShader.h"

#include "./Framework/Core/D3D11/OMStage/RenderTexture.h"

//Subsystem
#include "./Framework/Core/Subsystem/Graphics.h"
#include "./Framework/Core/Subsystem/Input.h"
#include "./Framework/Core/Subsystem/Timer.h"
#include "./Framework/Core/Subsystem/SceneManager.h"
#include "./Framework/Core/Subsystem/ResourceManager.h"
#include "./Framework/Core/Subsystem/DirectWriter.h"
#include "./Framework/Core/Subsystem/Audio.h"
#include "./Framework/Core/Subsystem/ColliderManager.h"
#include "./Framework/Core/Subsystem/Renderer.h"
#include "./Framework/Core/Subsystem/Scripting.h"
#include "./Framework/Core/Subsystem/Engine.h"

//Utility
#include "./Framework/Utility/Xml.h"
#include "./Framework/Utility/FileSystem.h"
#include "./Framework/Utility/GeometryUtility.h"

//Resource
#include "./Framework/Resource/Shader.h"
#include "./Framework/Resource/Texture.h"
#include "./Framework/Resource/Material.h"
#include "./Framework/Resource/Animation.h"
#include "./Framework/Resource/AudioClip.h"