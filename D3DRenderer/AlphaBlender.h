#pragma once
#include "Bindable.h"
#include <array>

class AlphaBlender : public Bindable
{
public:
	AlphaBlender(Graphics & gfx, bool toBlend);
	void Bind(Graphics& gfx) override;
	static std::shared_ptr<AlphaBlender> Resolve(Graphics& gfx, bool toBlend);
protected:
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlender;
	bool toBlend;
};

