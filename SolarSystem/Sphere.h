#pragma once
#include "DXRenderer.h"
#include <fstream>
#include <vector>
class Sphere {
private:
	struct Vertex
	{
		float x, y, z;
		float r, g, b,a;
	};
	struct Triangle
	{
		Vertex vertex[3];
	};

	std::vector<Triangle> TriangleList;
	std::vector<Vertex> VerticesList;
	ID3D11Buffer * m_vertexBuffer;
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader * m_pixelShader;
	ID3D11InputLayout * m_inputLayout;
public:
	Sphere(DXRenderer &renderer);
	~Sphere();
	void draw(DXRenderer &renderer);
	void createIcosahedron();
	void createVertexBuffer(DXRenderer &renderer);
	void createShaders(DXRenderer &renderer);

};