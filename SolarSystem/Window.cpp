#include "Window.h"
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

Window::Window(int width, int height, HINSTANCE hInstance)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;
	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "MyClass";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	m_handle = CreateWindowEx(NULL,
		"MyClass",    // name of the window class
		"SolarSystem",   // title of the window
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,    // window style
		(GetSystemMetrics(SM_CXSCREEN)-width)/2,    // x-position of the window
		(GetSystemMetrics(SM_CYSCREEN)-height)/2,    // y-position of the window
		width,    // width of the window
		height,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL
}

HWND Window::getHandle()
{
	return m_handle;
}





