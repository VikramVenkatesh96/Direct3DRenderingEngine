#pragma once
#include "WinHeaderOptimizer.h"
#include "Colors.h"
#include <string>
class Surface
{
public:
	Surface(const std::wstring &filename);
	~Surface();
	void PutPixel(int x, int y, Color color);
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	Color* GetBufferPtr();
	const Color* GetBufferPtr() const;
	static Surface FromFile(const std::wstring& filename);
private:
	std::unique_ptr<Color[]> pBuffer;
	unsigned int width;
	unsigned int height;
};
