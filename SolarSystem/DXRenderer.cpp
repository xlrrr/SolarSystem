#include "DXRenderer.h"

DXRenderer::DXRenderer(Window & window)
{
	m_swapChain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilState = nullptr;
	m_depthStencilView = nullptr;
	m_depthStencilBuffer = nullptr;
	createDevice(window);
	createRenderTarget();
	createDepthBuffer();
}


void DXRenderer::createDevice(Window & window)
{
	//Define swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.getHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;
	//Create swap chain and device
	auto result = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_deviceContext);
	if (result == S_OK) {
		MessageBox(nullptr, "DirectX 11 Initialized", "Success", MB_OK);
	}
	else {
		MessageBox(nullptr, "DX11 Failed to initialize", "Error", MB_OK);
		exit(0);
	}
}

void DXRenderer::createRenderTarget()
{
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->Release();
}

void DXRenderer::createDepthBuffer()
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	depthBufferDesc.Width = 1024;
	depthBufferDesc.Height = 768;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);


	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	// Depth test parameters
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	// Stencil test parameters
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);


	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);

}


void DXRenderer::beginFrame()
{
	//bind render target
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	//Set viewport
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, 1024.f, 768.f);
	m_deviceContext->RSSetViewports(1, &viewport);

	//Setting bg color
	float color[] = { .25f, .1f,.25f,1 };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
}

void DXRenderer::endFrame()
{
	//swapping the buffer
	m_swapChain->Present(1, 0);
}

DXRenderer::~DXRenderer()
{
	m_swapChain->Release();
	m_device->Release();
	m_deviceContext->Release();
	m_renderTargetView->Release();
	m_depthStencilState->Release();
	m_depthStencilView->Release();
		m_depthStencilBuffer->Release();
}

ID3D11Device * DXRenderer::getDevice()
{
	return m_device;
}

ID3D11DeviceContext * DXRenderer::getDeviceContext()
{
	return m_deviceContext;
}

ID3D11RenderTargetView * DXRenderer::getRenderTargetView()
{
	return m_renderTargetView;
}

IDXGISwapChain * DXRenderer::getSwapChain()
{
	return m_swapChain;
}
