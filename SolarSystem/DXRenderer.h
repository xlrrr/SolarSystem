#pragma once
#include "Window.h"
#include <d3d11.h>

class DXRenderer {
private:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Texture2D* m_depthStencilBuffer;
	void createDevice(Window &window);
	void createRenderTarget();
	void createDepthBuffer();
public:
	DXRenderer(Window &window);
	~DXRenderer();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	void beginFrame();
	void endFrame();
};