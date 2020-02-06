#include "Box.h"
#include "BindableBase.h"
#include"Rect.h"

Box::Box(Graphics & gfx, std::mt19937 & rng, std::uniform_real_distribution<float>& aDist, std::uniform_real_distribution<float>& dDist, std::uniform_real_distribution<float>& oDist, std::uniform_real_distribution<float>& rDist)
	:r(rDist(rng)),
	dRoll(dDist(rng)),
	dPitch(dDist(rng)),
	dYaw(dDist(rng)),
	dPhi(oDist(rng)),
	dTheta(oDist(rng)),
	dChi(oDist(rng)),
	chi(aDist(rng)),
	theta(aDist(rng)),
	phi(aDist(rng))
{
	namespace dx = DirectX;
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};

		auto model = Rect::Make<Vertex>();
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));
		auto pVS = std::make_unique<VertexShader>(gfx, "VertexShader.cso");
		auto pBC = pVS->GetBytecode();
		AddStaticBind(std::move(pVS));

		AddStaticBind(std::make_unique<PixelShader>(gfx, "PixelShader.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pBC));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}
	AddBind(std::make_unique<TransformCBuf>(gfx, *this));
	/*if (!IsStaticInitialized())
	{
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
		const std::vector<Vertex> vertices =
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

		AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

		const std::vector<unsigned short> indices =
		{
			0, 2, 1,	2, 3, 1,
			1, 3, 5,	3, 7, 5,
			2, 6, 3,	3, 6, 7,
			4, 5, 7,	4, 7, 6,
			0, 4, 2,	2, 4, 6,
			0, 1, 4,	1, 5, 4,
		};

		AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		auto pVS = std::make_unique<VertexShader>(gfx, "VertexShader.cso");
		auto pBC = pVS->GetBytecode();
		AddBind(std::move(pVS));

		AddBind(std::make_unique<PixelShader>(gfx, "PixelShader.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		AddBind(std::make_unique<InputLayout>(gfx, ied, pBC));

		AddBind(std::make_unique<Topology>(gfx, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}
	AddBind(std::make_unique<TransformCBuf>(gfx, *this));*/
}

void Box::Update(float dt)
{
	roll += dRoll * dt;
	pitch += dPitch * dt;
	yaw += dYaw * dt;
	theta += dTheta * dt;
	phi += dPhi * dt;
	chi += dChi * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f)*
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}
