#pragma once
#include "WinHeaderOptimizer.h"
#include "EngineExceptions.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <wrl.h>

class Graphics
{
	friend class Bindable;

public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	void BeginFrame(float r, float g, float b);
	void EndFrame();
	void SetProjection(DirectX::FXMMATRIX proj);
	DirectX::XMMATRIX GetProjection() const;

	void SetCamera(DirectX::FXMMATRIX cam);
	DirectX::XMMATRIX GetCamera() const;
	void EnableImGui();
	void DisableImGui();
	bool IsImGuiEnabled() const;
	void DrawTriangle(float, float, float, float);
	void DrawIndexed(UINT count);


private:
	bool imguiEnabled = true;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
};

