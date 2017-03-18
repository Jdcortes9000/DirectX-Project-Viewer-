#pragma once

namespace DX11UWA
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model[3];
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
		DirectX::XMFLOAT4X4 lightViewMatrix;
		DirectX::XMFLOAT4X4 lightProjectionMatrix;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT4 pos;
		DirectX::XMFLOAT4 color;
	};

	struct VertexPositionUVNormal
	{
		DirectX::XMFLOAT4 pos;
		DirectX::XMFLOAT4 uv;
		DirectX::XMFLOAT4 normal;
	};
}