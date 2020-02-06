#include "WinApp.h"
#include "Box.h"
#include "Sheet.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "ImGUI/imgui.h"
#include <memory>

GDIPlusManager gdipManager;

WinApp::WinApp()
	:win(800, 600, "MEngine")
{
	//Fill in drawables list
	drawables.push_back(std::make_unique<Sheet>(win.Gfx(), L"Images\\SpaceOptimized.png", 12.0f, 16.0f, 0.0f, 0.01f));
	drawables.push_back(std::make_unique<Sheet>(win.Gfx(), L"Images\\Ring.png", 0.75f, 0.75f, 0.5f, -1.0f));

	win.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 1000.0f));
}

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

WinApp::~WinApp()
{
	gdipManager.~GDIPlusManager();
}

void WinApp::UpdateFrame()
{
	const float dt = timer.Mark();
	win.Gfx().BeginFrame(0.0f, 0.0f, 0.0f);
	win.Gfx().SetCamera(camera.GetMatrix());

	for (auto& d : drawables)
	{
		d->Update(dt);
		d->Draw(win.Gfx());
	}
	if (win.kbd.IsKeyPressed(VK_SPACE))
	{
		debug.Log("Yo!");
	}

	if (show_demo_window)
	{
		camera.ControlWindow();
		debug.Draw();
	}
	

	win.Gfx().EndFrame();
}
