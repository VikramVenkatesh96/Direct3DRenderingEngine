#include "VertexShader.h"
#include "StringUtils.h"

VertexShader::VertexShader(Graphics & gfx, const std::string& path) 
	: path(path)
{
	D3DReadFileToBlob(ToWide(path).c_str(), &pByteCodeBlob);
	GetDevice(gfx)->CreateVertexShader(pByteCodeBlob->GetBufferPointer(), pByteCodeBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void VertexShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob * VertexShader::GetBytecode() const
{
	return pByteCodeBlob.Get();
}
