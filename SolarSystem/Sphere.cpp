#include "Sphere.h"

Sphere::Sphere(DXRenderer & renderer)
{
	m_vertexBuffer = nullptr;
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_inputLayout = nullptr;
	createIcosahedron();
	createVertexBuffer(renderer);
	createShaders(renderer);
}

Sphere::~Sphere()
{
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
}

void Sphere::draw(DXRenderer & renderer)
{

	auto deviceContext = renderer.getDeviceContext();
	float color[] = { 0.f,0.f,0.f,1.f };
	deviceContext->ClearRenderTargetView(renderer.getRenderTargetView(), color);

	//Bind shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
	//Binding vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->Draw(VerticesList.size(), 0);

}

void Sphere::createIcosahedron()
{
	const float X = .525731112119133606f;
	const float Z = .850650808352039932f;
	const float N = 0.f;
	VerticesList =
	{
		{ -X,N,Z ,1.f,0.f,0.f,1.f},
		{ X,N,Z ,1.f,0.f,0.f,1.f },
		{ -X,N,-Z,1.f,0.f,0.f,1.f },
		{ X,N,-Z,1.f,0.f,0.f,1.f },
		{ N,Z,X ,1.f,0.f,0.f,1.f },
		{ N,Z,-X ,1.f,0.f,0.f,1.f },
		{ N,-Z,X ,1.f,0.f,0.f,1.f },
		{ N,-Z,-X,1.f,0.f,0.f,1.f },
		{ Z,X,N ,1.f,0.f,0.f,1.f },
		{ -Z,X, N,1.f,0.f,0.f,1.f },
		{ Z,-X,N ,1.f,0.f,0.f,1.f },
		{ -Z,-X, N ,1.f,0.f,0.f,1.f }
	};
	TriangleList =
	{
		{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
		{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
		{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
		{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 }
	};
}

void Sphere::createVertexBuffer(DXRenderer& renderer)
{
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(VerticesList), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &VerticesList;

	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
}

void Sphere::createShaders(DXRenderer & renderer)
{
	//creating shaders
	std::ifstream vsFile("SphereVertexShader.cso", std::ios::binary);
	std::ifstream psFile("SpherePixelShader.cso", std::ios::binary);
	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile),std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
	renderer.getDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	renderer.getDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);
	vsFile.close();
	psFile.close();

	//creating input layout we can't have another function since we need the data 
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	renderer.getDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}




