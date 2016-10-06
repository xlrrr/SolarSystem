#include "DXRenderer.h"

DXRenderer::DXRenderer(Window & window)
{
	m_swapChain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	//Define swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.getHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;
	//Create swap chain and device
	auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc,
		&m_swapChain, &m_device, nullptr, &m_deviceContext);
	if (result == S_OK) {
		MessageBox(nullptr, "DirectX 11 Initialized", "Success", MB_OK);
	}
	else {
		MessageBox(nullptr, "DX11 Failed to initialize", "Error", MB_OK);
	}
}

DXRenderer::~DXRenderer()
{
	m_swapChain->Release();
	m_device->Release();
	m_deviceContext->Release();
}
