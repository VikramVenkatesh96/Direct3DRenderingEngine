#include "AlphaBlender.h"

AlphaBlender::AlphaBlender(Graphics & gfx, bool toBlend)
	:toBlend(toBlend)
{
	D3D11_BLEND_DESC blendDesc = {};
	auto& bRT = blendDesc.RenderTarget[0];
	if (toBlend)
	{
		bRT.BlendEnable = TRUE;
		bRT.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bRT.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bRT.BlendOp = D3D11_BLEND_OP_ADD;
		bRT.SrcBlendAlpha = D3D11_BLEND_ZERO;
		bRT.DestBlendAlpha = D3D11_BLEND_ZERO;
		bRT.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	}
	else
	{
		bRT.BlendEnable = FALSE;
	}

	bRT.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	GetDevice(gfx)->CreateBlendState(&blendDesc, &pBlender);
}

void AlphaBlender::Bind(Graphics & gfx)
{
	GetContext(gfx)->OMSetBlendState(pBlender.Get(),nullptr,0XFFFFFFFFu);
}

std::shared_ptr<AlphaBlender> AlphaBlender::Resolve(Graphics & gfx, bool toBlend)
{
	return std::shared_ptr<AlphaBlender>();
}
