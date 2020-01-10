#pragma once
#include "Window.h"
#include "Timer.h"

class WinApp
{
public:
    WinApp();
    int Run();
private:
    void UpdateFrame();
private:
    Window win;
    Timer timer;
};

