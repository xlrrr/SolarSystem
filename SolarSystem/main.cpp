#include <windows.h>
#include <windowsx.h>
#include "Window.h"
#include "DXRenderer.h"
#include "Sphere.h"


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	Window window(1024, 768, hInstance);
	DXRenderer renderer(window);
	Sphere sphere(renderer);
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) break;
		}
		renderer.beginFrame();
		sphere.draw(renderer);
		renderer.endFrame();
	}
	return msg.wParam;
}

