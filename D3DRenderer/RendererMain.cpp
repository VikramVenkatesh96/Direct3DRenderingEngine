#include "WinApp.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrev,
	LPSTR lpCMD,
	int cmdDisp
)
{
	return WinApp{}.Run();
}