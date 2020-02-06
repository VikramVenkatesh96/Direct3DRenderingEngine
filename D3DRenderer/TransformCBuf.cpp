#include "TransformCBuf.h"

std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> TransformCBuf::pVCBuf;

TransformCBuf::TransformCBuf(Graphics& gfx, const Drawable& parent)
	:parent(parent)
{
	if (!pVCBuf)
	{
		pVCBuf = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	}
}

void TransformCBuf::Bind(Graphics& gfx)
{
	pVCBuf->Update(gfx, DirectX::XMMatrixTranspose(parent.GetTransformXM() * gfx.GetCamera() * gfx.GetProjection()));
	pVCBuf->Bind(gfx);
}