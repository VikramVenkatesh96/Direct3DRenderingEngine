#include "Sheet.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"
#include "BindableBase.h"
#include "Rect.h"

Sheet::Sheet(Graphics & gfx, std::wstring fileName, float xScale, float yScale, float yVel, float dRoll)
	:fileName(fileName),
	 xScale(xScale),
	 yScale(yScale),
	 r(0),
	 y(0),
	 yVel(yVel),
	dRoll(dRoll),
	dPitch(0),
	dYaw(0),
	dPhi(0),
	dTheta(0),
	dChi(0),
	chi(0),
	theta(0),
	phi(0)
{
	namespace dx = DirectX;
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			struct
			{
				float u;
				float v;
			}tex;
		};

		auto model = Rect::Make<Vertex>();
		model.vertices[0].tex = { 0.0f, 1.0f };
		model.vertices[1].tex = { 1.0f, 1.0f };
		model.vertices[2].tex = { 0.0f, 0.0f };
		model.vertices[3].tex = { 1.0f, 0.0f };

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		AddStaticBind(std::make_unique<Sampler>(gfx));

		//Alpha blending code. Doing Alpha Testing in PixelShader instead
		//AddStaticBind(std::make_unique<AlphaBlender>(gfx, true));

		auto pVS = std::make_unique<VertexShader>(gfx, "TextureVS.cso");
		auto pBC = pVS->GetBytecode();
		AddStaticBind(std::move(pVS));

		AddStaticBind(std::make_unique<PixelShader>(gfx, "TexturePS.cso"));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));
		

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pBC));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<Texture>(gfx, Surface::FromFile(fileName)));
	AddBind(std::make_unique<TransformCBuf>(gfx, *this));
}

void Sheet::Update(float dt)
{
	y -= yVel * dt;
	roll += dRoll * dt;
	pitch += dPitch * dt;
	yaw += dYaw * dt;
	theta += dTheta * dt;
	phi += dPhi * dt;
	chi += dChi * dt;
}

DirectX::XMMATRIX Sheet::GetTransformXM() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(0.0f, y, 0.0f)*
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi)*
		DirectX::XMMatrixScaling(xScale, yScale, 1.0f);
}
