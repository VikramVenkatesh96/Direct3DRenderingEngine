#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics & gfx, const std::vector<unsigned short>& indices)
	:count((UINT)indices.size())
{
	D3D11_BUFFER_DESC indexBD = {};
	indexBD.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBD.Usage = D3D11_USAGE_DEFAULT;
	indexBD.CPUAccessFlags = 0u;
	indexBD.MiscFlags = 0u;
	indexBD.ByteWidth = UINT(count * sizeof(unsigned short));
	indexBD.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSD = {};
	indexSD.pSysMem = indices.data();
	GetDevice(gfx)->CreateBuffer(&indexBD, &indexSD, pIndexBuffer.GetAddressOf());
	
}


void IndexBuffer::Bind(Graphics & gfx) noexcept
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const
{
	return count;
}

