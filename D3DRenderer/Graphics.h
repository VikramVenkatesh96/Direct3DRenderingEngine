#pragma once
#include "WinHeaderOptimizer.h"
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float r, float g, float b)
	{
		const float color[] = { r, g, b, 1.0f };
		pContext->ClearRenderTargetView(pRenderTarget.Get(), color);
	}
	void DrawTriangle();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTarget;
};

