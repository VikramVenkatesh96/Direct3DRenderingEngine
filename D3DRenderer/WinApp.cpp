#include "WinApp.h"

WinApp::WinApp()
	:win(800, 600, "MEngine")
{}

int WinApp::Run()
{
	while (true)
	{
		if (const auto eCode = Window::ProcessMessages())
		{
			return *eCode;
		}

		UpdateFrame();
	}
}

void WinApp::UpdateFrame()
{
	const float dt = timer.Peek();
	win.Gfx().ClearBuffer(1.0f, 0.0f, 0.0f);
	win.Gfx().EndFrame();
}
