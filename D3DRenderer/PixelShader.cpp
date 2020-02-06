#include "PixelShader.h"
#include "StringUtils.h"
#include <typeinfo>

PixelShader::PixelShader(Graphics & gfx, const std::string& path)
	:path(path)
{
	D3DReadFileToBlob(ToWide(path).c_str(), &pByteCodeBlob);
	GetDevice(gfx)->CreatePixelShader(pByteCodeBlob->GetBufferPointer(), pByteCodeBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}

ID3DBlob * PixelShader::GetBytecode() const
{
	return nullptr;
}
