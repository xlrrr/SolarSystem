#pragma once
#include <Windows.h>
class Window {
private:
	HWND m_handle;

public:
	Window(int width, int height, HINSTANCE hInstance);
	HWND getHandle();
};