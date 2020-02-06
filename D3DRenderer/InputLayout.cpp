#include "InputLayout.h"

InputLayout::InputLayout(Graphics & gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob * pBlob)
{

	GetDevice(gfx)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);
}

void InputLayout::Bind(Graphics & gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}
