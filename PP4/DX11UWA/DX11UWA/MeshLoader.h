#pragma once

#include<vector>

#include "pch.h"
#include "..\Common\DeviceResources.h"
#include "..\Content\ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "..\Common\DirectXHelper.h"
#include "..\Content\Sample3DSceneRenderer.h"
#include "..\Content\Sample3DSceneRenderer.cpp"

//struct MeshStruct
//{
//	DirectX::XMFLOAT3 pos;
//	DirectX::XMFLOAT3 uv;
//	DirectX::XMFLOAT3 norm;
//};



struct LoadedMeshStuff
{
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;
	DX11UWA::VertexPositionColor * theMeshVertices;
	static const unsigned short meshIndices[];
	uint32 m_indexCount;
};
char objText[128];
LoadedMeshStuff MESH;
void loadMesh()
{

	std::vector <unsigned int> vertexIdx, uvIdx, normalIdx;
	std::vector <DirectX::XMVECTOR> tempVerts;
	std::vector <DirectX::XMVECTOR> tempUV;
	std::vector <DirectX::XMVECTOR> tempNorms;
	FILE *file = fopen("Assets/palmTree.obj", "r");
	if (file != NULL)
	{
		while (true)
		{
			int res = fscanf_s(file, "%s", objText);
			if (res == EOF)
				break;
			else
			{
				if (strcmp(objText, "v") == 0)
				{
					DirectX::XMVECTOR vec;
					fscanf_s(file, "%f %f %f\n", &vec.m128_f32[0], &vec.m128_f32[1], &vec.m128_f32[2]);
					tempVerts.push_back(vec);

				}
				else if (strcmp(objText, "vt") == 0)
				{
					DirectX::XMVECTOR vec;
					fscanf_s(file, "%f %f\n", &vec.m128_f32[0], &vec.m128_f32[1]);
					tempUV.push_back(vec);

				}
				else if (strcmp(objText, "vn") == 0)
				{
					DirectX::XMVECTOR vec;
					fscanf_s(file, "%f %f %f\n", &vec.m128_f32[0], &vec.m128_f32[1], &vec.m128_f32[2]);
					tempNorms.push_back(vec);

				}
				else if (strcmp(objText, "f") == 0)
				{
					std::string vertex1, vertex2, vertex3;
					unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
					int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (matches == 9)
					{
						vertexIdx.push_back(vertexIndex[0]);
						vertexIdx.push_back(vertexIndex[1]);
						vertexIdx.push_back(vertexIndex[2]);
						uvIdx.push_back(uvIndex[0]);
						uvIdx.push_back(uvIndex[1]);
						uvIdx.push_back(uvIndex[2]);
						normalIdx.push_back(normalIndex[0]);
						normalIdx.push_back(normalIndex[1]);
						normalIdx.push_back(normalIndex[2]);
					}
				}
			}
		}
	}
	

	VertexPositionColor *model = new VertexPositionColor[tempVerts.size()];
	for (unsigned int i = 0; i < vertexIdx.size(); i++)
	{
		unsigned int idx = vertexIdx[i];
		DirectX::XMVECTOR temp = tempVerts[idx - 1];
		DirectX::XMStoreFloat3(&model[i].pos, temp);
	}
	MESH.theMeshVertices = model;

//	auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
//	auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");
//	
//	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData)
//	{
//		DX::ThrowIfFailed(m_deviceResources->GetD3DDevice()->CreateVertexShader(&fileData[0], fileData.size(), nullptr, &MESH.m_vertexBuffer));
//
//		static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "UV", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		};
//
//		DX::ThrowIfFailed(m_deviceResources->GetD3DDevice()->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), &fileData[0], fileData.size(), &MESH.m_inputLayout));
//	});
//
//	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData)
//	{
//		DX::ThrowIfFailed(m_deviceResources->GetD3DDevice()->CreatePixelShader(&fileData[0], fileData.size(), nullptr, &m_pixelShader));
//
//		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
//		DX::ThrowIfFailed(m_deviceResources->GetD3DDevice()->CreateBuffer(&constantBufferDesc, nullptr, &MESH.m_constantBuffer));
//	});
//
//	auto createCubeTask = (createPSTask && createVSTask).then([this]()
//	{
//		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
//		vertexBufferData.pSysMem = &MESH.theMeshVertices;
//		vertexBufferData.SysMemPitch = 0;
//		vertexBufferData.SysMemSlicePitch = 0;
//		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(&MESH.theMeshVertices), D3D11_BIND_VERTEX_BUFFER);
//		DX::ThrowIfFailed(m_deviceResources->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &MESH.m_vertexBuffer));
//
//		unsigned short meshIndices[vertexIdx.size()];
//		for (int i = 0; i < meshIndices; i++)
//		{
//			meshIndices[i] = vertexIdx[i];
//		}
//		MESH.m_indexCount = ARRAYSIZE(meshIndices);
//		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
//		indexBufferData.pSysMem = meshIndices;
//		indexBufferData.SysMemPitch = 0;
//		indexBufferData.SysMemSlicePitch = 0;
//		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(meshIndices), D3D11_BIND_INDEX_BUFFER);
//		DX::ThrowIfFailed(m_deviceResources->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, &MESH.m_indexBuffer));
//	});
//
//	createCubeTask.then([this]()
//	{
//		m_loadingComplete = true;
//	});
}
//void RenderMesh()
//{
//	
//	loadMesh();
//	auto context = m_deviceResources->GetD3DDeviceContext();
//
//	XMStoreFloat4x4(&MESH.m_constantBufferData.view, XMMatrixTranspose(XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_camera))));
//
//
//	// Prepare the constant buffer to send it to the graphics device.
//	context->UpdateSubresource1(MESH.m_constantBuffer.Get(), 0, NULL, &MESH.m_constantBufferData, 0, 0, 0);
//	// Each vertex is one instance of the VertexPositionColor struct.
//	UINT stride = sizeof(VertexPositionColor);
//	UINT offset = 0;
//	context->IASetVertexBuffers(0, 1, MESH.m_vertexBuffer.GetAddressOf(), &stride, &offset);
//	// Each index is one 16-bit unsigned integer (short).
//	context->IASetIndexBuffer(MESH.m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	context->IASetInputLayout(MESH.m_inputLayout.Get());
//	// Attach our vertex shader.
//	context->VSSetShader(MESH.m_vertexShader.Get(), nullptr, 0);
//	// Send the constant buffer to the graphics device.
//	context->VSSetConstantBuffers1(0, 1, MESH.m_constantBuffer.GetAddressOf(), nullptr, nullptr);
//	// Attach our pixel shader.
//	context->PSSetShader(MESH.m_pixelShader.Get(), nullptr, 0);
//	// Draw the objects.
//	context->DrawIndexed(MESH.m_indexCount, 0, 0);
//}