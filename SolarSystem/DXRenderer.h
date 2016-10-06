#pragma once
#include "Window.h"
#include <d3d11.h>

class DXRenderer {
private:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
public:
	DXRenderer(Window &window);
	~DXRenderer();
};