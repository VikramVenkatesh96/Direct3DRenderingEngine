#include "Graphics.h"
#include "GraphicsThrowMacros.h"
#include "ImGUI/imgui.h"
#include "ImGUI/examples/imgui_impl_win32.h"
#include "ImGUI/examples/imgui_impl_dx11.h"
#include <iterator>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 0;
	desc.BufferDesc.RefreshRate.Denominator = 0;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.OutputWindow = hWnd;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0, nullptr, 0, D3D11_SDK_VERSION, &desc,
		pSwapChain.GetAddressOf(), pDevice.GetAddressOf(), nullptr, pContext.GetAddressOf()
	);

	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pRenderTarget.GetAddressOf());
	pBackBuffer->Release();

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 800u;
	descDepth.Height = 600u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 1u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDepthStencilView);
	pContext->OMSetRenderTargets(1u, pRenderTarget.GetAddressOf(), pDepthStencilView.Get());

	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);

	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}

void Graphics::BeginFrame(float r, float g, float b)
{
	if (imguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	const float color[] = { r, g, b, 1.0f };
	pContext->ClearRenderTargetView(pRenderTarget.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::EndFrame()
{
	if (imguiEnabled)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	pSwapChain->Present(1u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj)
{
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const
{
	return projection;
}

void Graphics::SetCamera(DirectX::FXMMATRIX cam)
{
	camera = cam;
}

DirectX::XMMATRIX Graphics::GetCamera() const
{
	return camera;
}

void Graphics::EnableImGui()
{
	imguiEnabled = true;
}

void Graphics::DisableImGui()
{
	imguiEnabled = false;
}

bool Graphics::IsImGuiEnabled() const
{
	return imguiEnabled;
}

void Graphics::DrawTriangle(float xOffset, float yOffset, float zOffset, float angle)
{
	namespace wrl = Microsoft::WRL;
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		}pos;

		struct
		{
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		}color;
	};

	const Vertex vertices[] =
	{
		{-1.0f, -1.0f, -1.0f,	255, 255, 255, 0},
		{ 1.0f, -1.0f, -1.0f,	255, 255, 255, 0},
		{-1.0f,  1.0f, -1.0f,	255, 255, 255, 0},
		{ 1.0f,  1.0f, -1.0f,	255, 255, 255, 0},
		{-1.0f, -1.0f,  1.0f,	255, 255, 255, 0},
		{ 1.0f, -1.0f,  1.0f,	255, 255, 255, 0},
		{-1.0f,  1.0f,  1.0f,	255, 255, 255, 0},
		{ 1.0f,  1.0f,  1.0f,	255, 255, 255, 0},
	};

	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;

	pDevice->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf());
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);


	const unsigned short indices[] =
	{
		0, 2, 1,	2, 3, 1,
		1, 3, 5,	3, 7, 5,
		2, 6, 3,	3, 6, 7,
		4, 5, 7,	4, 7, 6,
		0, 4, 2,	2, 4, 6,
		0, 1, 4,	1, 5, 4,
	};

	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC indexBD = {};
	indexBD.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBD.Usage = D3D11_USAGE_DEFAULT;
	indexBD.CPUAccessFlags = 0u;
	indexBD.MiscFlags = 0u;
	indexBD.ByteWidth = sizeof(indices);
	indexBD.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSD = {};
	indexSD.pSysMem = indices;
	pDevice->CreateBuffer(&indexBD, &indexSD, pIndexBuffer.GetAddressOf());
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	struct ConstantBuffer
	{
		dx::XMMATRIX transformation;

	};

	const ConstantBuffer cb =
	{
		{
				dx::XMMatrixTranspose
				(
				dx::XMMatrixRotationY(angle) *
				dx::XMMatrixTranslation(xOffset, yOffset, zOffset) *
				dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f)
				)
		}
	};

	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cBD = {};
	cBD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBD.ByteWidth = sizeof(cb);
	cBD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBD.MiscFlags = 0u;
	cBD.StructureByteStride = 0u;
	cBD.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA cSD = {};
	cSD.pSysMem = &cb;
	pDevice->CreateBuffer(&cBD, &cSD, &pConstantBuffer);
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	pDevice->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);

	pContext->IASetInputLayout(pInputLayout.Get());

	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);

	pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
}

void Graphics::DrawIndexed(UINT count)
{
	pContext->DrawIndexed(count, 0u, 0u);
}



