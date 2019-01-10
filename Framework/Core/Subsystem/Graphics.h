#pragma once

//Device, DeviceContext 관리하는놈
class Graphics : public ISubsystem
{
public:
	Graphics(class Context* context);
	virtual ~Graphics();

	//Getter=================================================================
	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }
	//=======================================================================

	const bool Initialize() override;//DirecxtX 11 의 초기화
	void Resize(const uint& width, const uint& height); //백버퍼를 만들어주는 함수

	//=========더블버퍼링======================================================
	void BeginScene(); //그리기 시작하는 함수
	void EndScene(); //그린걸 출력하는 함수
	//========================================================================

private:
	ID3D11Device* device; // 뭔가 만드는놈
	ID3D11DeviceContext* deviceContext;// 뭔가 그리는놈(세팅하는놈)
	IDXGISwapChain* swapChain; // 더블 버퍼링

							   //일단 넘어감
	ID3D11Debug* debugDevice;
	uint gpuMemorySize;
	wstring gpuDescription;
	uint numerator;
	uint denominator;

	D3DXCOLOR clearColor;//하나씩 지우면 처리비용이 비싸기때문에 색을 덮어씌워서 지움, 그때 사용하는 색상
	ID3D11DepthStencilView* depthStencilView; //메인 깊이버퍼
	ID3D11RenderTargetView* renderTargetView; // 매인 렌더타겟버퍼
	D3D11_VIEWPORT viewport;//렌더타겟을 윈도우창 어느 영역에 표시할지에 대한 좌표값, 보여질 영역
};