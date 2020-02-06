#define FULL_WIN_INCLUDE
#include "WinHeaderOptimizer.h"
#include "Surface.h"
#include <algorithm>
#include <codecvt>
#ifdef DEBUG
#include <assert.h>
#endif 
#include <fstream>
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <gdiplus.h>

namespace gdi = Gdiplus;


Surface::Surface(const std::wstring &filename)
{
	gdi::Bitmap bitmap(filename.c_str());
	if (bitmap.GetLastStatus() != gdi::Ok)
	{
		std::string narrow(filename.begin(), filename.end());
		
		throw std::runtime_error("Surface::Surface failed to load file: " + narrow);
	}
	width = bitmap.GetWidth();
	height = bitmap.GetHeight();
	pBuffer = std::make_unique<Color[]>(width* height);

	const BOOL isAlpha = gdi::IsAlphaPixelFormat(bitmap.GetPixelFormat());

	for (int y = 0; y < height; ++y) 
	{
		for (int x = 0; x < width; ++x) 
		{
		
			gdi::Color pixelColor;
			bitmap.GetPixel(x, y, &pixelColor);
			if (isAlpha == TRUE)
			{
				PutPixel(x, y, { pixelColor.GetA(), pixelColor.GetR() ,pixelColor.GetG() ,pixelColor.GetB() });
			}
			else
			{
				PutPixel(x, y, { pixelColor.GetR() ,pixelColor.GetG() ,pixelColor.GetB() });
			}
		}
	}
}

Surface::~Surface()
{
}


void Surface::PutPixel(int x, int y, Color color)
{
#ifdef DEBUG
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
#endif
	pBuffer[y * width + x] = color;
}

unsigned int Surface::GetWidth() const
{
	return width;
}

unsigned int Surface::GetHeight() const
{
	return height;
}

Color * Surface::GetBufferPtr()
{
	return pBuffer.get();
}

const Color * Surface::GetBufferPtr() const
{
	return pBuffer.get();
}

Surface Surface::FromFile(const std::wstring & filename)
{
	return Surface(filename);
}

