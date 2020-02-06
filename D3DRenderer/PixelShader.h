#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::string& path);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetBytecode() const;
protected:
	std::string path;
	Microsoft::WRL::ComPtr<ID3DBlob> pByteCodeBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};

