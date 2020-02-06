#pragma once
#include "Window.h"
#include "Timer.h"
#include "ImGUIManager.h"
#include "Camera.h"
#include "Debug.h"
#include <vector>


class Sheet;

class WinApp
{
public:
    WinApp();
    int Run();
	~WinApp();
private:
    void UpdateFrame();
private:
	bool show_demo_window = true;
	ImGUIManager GUIManager;
    Window win;
    Timer timer;
	Camera camera;
	Debug debug;
	std::vector<std::unique_ptr<class Drawable>> drawables;
};

