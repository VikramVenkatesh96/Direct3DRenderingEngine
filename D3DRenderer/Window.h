#pragma once
#include "WinHeaderOptimizer.h"
#include "EngineExceptions.h"
#include "Graphics.h"
#include "KeyBoard.h"
#include <memory>
#include <optional>

class Window
{
public:
	Window(int width, int height, const char* name);
	~Window();
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();

private:
	class WindowClass
	{
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();

	private:
		WindowClass();
		~WindowClass();
		static constexpr const char* winClassName = "MEngine Window";
		static WindowClass winClass;
		HINSTANCE hInstance;
	};

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	KeyBoard kbd;

private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

