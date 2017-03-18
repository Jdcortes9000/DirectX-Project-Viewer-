#pragma once

#include "pch.h"

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "Assets\Chest2_Diffuse.h"
#include "DDSTextureLoader.h"

using namespace DirectX;
namespace DX11UWA
{
	// This sample renderer instantiates a basic rendering pipeline.
	
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources(void);
		void CreateWindowSizeDependentResources(void);
		void ReleaseDeviceDependentResources(void);
		void Update(DX::StepTimer const& timer);
		void Render(void);
		void StartTracking(void);
		void TrackingUpdate(float positionX);
		void StopTracking(void);
		inline bool IsTracking(void) { return m_tracking; }

		// Helper functions for keyboard and mouse input
		void SetKeyboardButtons(const char* list);
		void SetMousePosition(const Windows::UI::Input::PointerPoint^ pos);
		void SetInputDeviceData(const char* kb, const Windows::UI::Input::PointerPoint^ pos);
		
		void UpdateSkybox(DX::StepTimer const& timer)
		{
			float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
			double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
			float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
			UpdateCamera(timer, 5.0f, 0.75f);
			pX = m_camera._41;
			pY = m_camera._42;
			pZ = m_camera._43;
			XMStoreFloat4x4(&m_constantBufferData.model[0], XMMatrixTranspose(XMMatrixTranslation(pX, pY, pZ)));
			
		}
		void BuildSkyBox()
		{
			static const VertexPositionUVNormal cubeVertices[] =
			{
		/*0*/   { XMFLOAT4(-0.5f, -0.5f, -0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
		/*1*/   { XMFLOAT4(-0.5f, -0.5f,  0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
		/*2*/   { XMFLOAT4(-0.5f,  0.5f, -0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
		/*3*/	{ XMFLOAT4(-0.5f,  0.5f,  0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },
		/*4*/	{ XMFLOAT4(0.5f,  -0.5f, -0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4(0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
		/*5*/	{ XMFLOAT4(0.5f,  -0.5f,  0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4(0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
		/*6*/	{ XMFLOAT4(0.5f,   0.5f, -0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4(0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
		/*7*/	{ XMFLOAT4(0.5f,   0.5f,  0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4(0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },
		/*8*/   { XMFLOAT4(-0.5f, -0.5f, -0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
		/*9*/	{ XMFLOAT4(-0.5f, -0.5f,  0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
		/*0*/	{ XMFLOAT4(-0.5f,  0.5f, -0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
		/*0*/	{ XMFLOAT4(-0.5f,  0.5f,  0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },
		/*0*/	{ XMFLOAT4(0.5f,  -0.5f, -0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
		/*0*/	{ XMFLOAT4(0.5f,  -0.5f,  0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
		/*0*/	{ XMFLOAT4(0.5f,   0.5f, -0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4(0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
		/*0*/	{ XMFLOAT4(0.5f,   0.5f,  0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4(0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },

			};
			vertexBufferData.pSysMem = cubeVertices;
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
			m_deviceResources->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);

			static const unsigned short cubeIndices[] =
			{
				10,9,8, // -x
				10,11,9,

				13,14,12, // +x
				15,14,13,

				1,5,0, // -y
				5,4,0,

				6,7,2, // +y
				7,3,2,

				4,6,0, // -z
				6,2,0,

				3,7,1, // +z
				7,5,1,
				/////////

			};

			m_indexCount = ARRAYSIZE(cubeIndices);
			indexBufferData.pSysMem = cubeIndices;
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
			m_deviceResources->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_indexBuffer);
		}
		void BuildCube()
		{
			
			static const VertexPositionUVNormal cubeVertices[] =
			{
				
				{ XMFLOAT4(-0.5f, -0.5f, -0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f, -0.5f,  0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f,  0.5f, -0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f,  0.5f,  0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,  -0.5f, -0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4( 0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,  -0.5f,  0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4( 0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,   0.5f, -0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4( 0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,   0.5f,  0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4( 0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f, -0.5f, -0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f, -0.5f,  0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f,  0.5f, -0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(-0.5f,  0.5f,  0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4(-0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,  -0.5f, -0.5f,1), XMFLOAT4(0.0f, 1.0f, 1.0f,1), XMFLOAT4( 0.377964497f, -0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,  -0.5f,  0.5f,1), XMFLOAT4(0.0f, 0.0f, 1.0f,1), XMFLOAT4( 0.377964497f, -0.377964497f,  0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,   0.5f, -0.5f,1), XMFLOAT4(1.0f, 1.0f, 1.0f,1), XMFLOAT4( 0.377964497f,  0.377964497f, -0.377964497f,0.755928993f) },
				{ XMFLOAT4(0.5f,   0.5f,  0.5f,1), XMFLOAT4(1.0f, 0.0f, 1.0f,1), XMFLOAT4( 0.377964497f,  0.377964497f,  0.377964497f,0.755928993f) },

			};
			vertexBufferData.pSysMem = cubeVertices;
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
			m_deviceResources->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);

			static const unsigned short cubeIndices[] =
			{
				8,9,10, // -x
				9,11,10,

				12,14,13, // +x
				13,14,15,

				0,5,1, // -y
				0,4,5,

				2,7,6, // +y
				2,3,7,

				0,6,4, // -z
				0,2,6,

				1,7,3, // +z
				1,5,7,
			};

			m_indexCount = ARRAYSIZE(cubeIndices);
			indexBufferData.pSysMem = cubeIndices;
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
			m_deviceResources->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_indexBuffer);
		}
		void BuildMesh()
		{
			vertexBufferData.pSysMem = MESH.theMeshVertices.data();
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(MESH.theMeshVertices.size() * sizeof(VertexPositionUVNormal), D3D11_BIND_VERTEX_BUFFER);
			m_deviceResources->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);

			m_indexCount = MESH.meshIndices.size();

			D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
			indexBufferData.pSysMem = MESH.meshIndices.data();
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(MESH.meshIndices.size() * sizeof(unsigned short), D3D11_BIND_INDEX_BUFFER);
			m_deviceResources->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_indexBuffer);
		}
		void LoadMeshFromFile(const char *path)
		{

			// TODO: Load mesh data and send it to the graphics card.
			std::fstream file;
			file.open(path, std::ios_base::in | std::ios_base::binary);
			if (file.is_open())
			{
				unsigned int meshLength = 0, textsize = 0;

				file.read((char*)&meshLength, sizeof(meshLength));
				std::string meshname;
				file.read((char*)meshname.c_str(), meshLength);
				file.read((char*)&textsize, sizeof(textsize));
				for (unsigned int i = 0; i < textsize; i++)
				{
					unsigned int textnum = 0;
					file.read((char*)&textnum, sizeof(textnum));
					char*Name = new char[textnum];
					file.read(Name, textnum);
					std::string name = Name;
					delete Name;
					size_t pos = name.find_last_of("/\\");
					name = name.substr(pos + 1);
					MESH.textureNames.push_back(name);
					//DXLayer.LoadTexture(name.c_str());
				}
				unsigned int vertNum = 0;
				file.read((char*)&vertNum, sizeof(vertNum));
				//std::vector<VertexPositionNormalTexture> vertData;
				for (unsigned int i = 0; i < vertNum; i++)
				{
					VertexPositionUVNormal data;
					file.read((char*)&data.pos.x, sizeof(data.pos.x));
					file.read((char*)&data.pos.y, sizeof(data.pos.y));
					file.read((char*)&data.pos.z, sizeof(data.pos.z));
					data.pos.w = 1;
					file.read((char*)&data.normal.x, sizeof(data.normal.x));
					file.read((char*)&data.normal.y, sizeof(data.normal.y));
					file.read((char*)&data.normal.z, sizeof(data.normal.z));
					data.normal.w = 1;
					file.read((char*)&data.uv.x, sizeof(data.uv.x));
					file.read((char*)&data.uv.y, sizeof(data.uv.y));
					data.uv.y = 1 - data.uv.y;
					data.uv.z = 1;
					data.uv.w = 1;
					MESH.theMeshVertices.push_back(data);
				}
				unsigned int triNum = 0;
				file.read((char*)&triNum, sizeof(triNum));
				//std::vector<unsigned int> indices;
				for (unsigned int i = 0; i < triNum * 3; i++)
				{
					unsigned int tri = 0;
					file.read((char*)&tri, sizeof(tri));

					MESH.meshIndices.push_back(tri);

				}
				//BufferInfo info;
				//DXLayer.LoadVertexAndIndexData_PosNormalTexture(&vertData.front(), vertData.size(), &indices.front(), indices.size(), &info);
				//buffer.push_back(info);
				file.close();
			}

		}

		void LoadTexture(std::string name)
		{
			std::wstring temp = std::wstring(name.begin(), name.end());
			const wchar_t* path = temp.c_str();
			m_device = m_deviceResources->GetD3DDevice();
			CreateDDSTextureFromFile(m_deviceResources->GetD3DDevice(), path,
				(ID3D11Resource **)m_modelTexture.Get(), m_SRV.GetAddressOf());
		}
		void LoadSecondTexture(std::string name)
		{
			std::wstring temp = std::wstring(name.begin(), name.end());
			const wchar_t* path = temp.c_str();
			m_device = m_deviceResources->GetD3DDevice();
			CreateDDSTextureFromFile(m_deviceResources->GetD3DDevice(), path,
				(ID3D11Resource **)m_modelTextureTwo.Get(), m_SRVTwo.GetAddressOf());
		}
		void LoadSkyBoxTexture(std::string name)
		{
			std::wstring temp = std::wstring(name.begin(), name.end());
			const wchar_t* path = temp.c_str();
			m_device = m_deviceResources->GetD3DDevice();
			CreateDDSTextureFromFile(m_device.Get(), path,
				NULL, m_SRV.GetAddressOf());
		}

		void CreateSkybox(std::string texture, float sx = 1, float sy = 1, float sz = 1)
		{
			sX = sx;
			sY = sy;
			sZ = sz;
			txNames.push_back(texture);
			createType = "Skybox";
			
			pixelShaderName = L"SkyBoxPixelShader.cso";
			vertexShaderName = L"SkyBoxVertexShader.cso";
			CreateDeviceDependentResources();
			
			
			pX = m_camera._41;
			pY = m_camera._42;
			pZ = m_camera._43;
			
		}

		void CreateMesh(const char *path, float x = 0, float y = 0, float z = 10, float rx = 0, float ry = 0, float rz = 0, float sx = 0.15, float sy = 0.15, float sz = 0.15)
		{
			if (path == "Assets/PALMTREE.mesh")
				modelAmount = 2;
			pX = x;
			pY = y;
			pZ = z;

			rX = rx;
			rY = ry;
			rZ = rz;

			sX = sx;
			sY = sy;
			sZ = sz;
			txNames.push_back(path);
			createType = "Mesh";
			
			CreateDeviceDependentResources();
			
			
		}

		void CreateCube(std::string texture, float x = 0, float y = 0, float z = 0, float rx = 0, float ry = 0, float rz = 0, float sx = 1, float sy = 1, float sz = 1, std::string texture2 = "n")
		{
			pixelShaderName = L"CubePixelShader.cso";

			if (texture == "Assets/cube.dds")
			{
				modelAmount = 3;
				IsTransparent = true;
			}
			if (modelAmount == 3)
			{
				D3D11_BLEND_DESC blendDesc = { 0 };
				blendDesc.AlphaToCoverageEnable = false;
				blendDesc.IndependentBlendEnable = false;
				blendDesc.RenderTarget[0].BlendEnable = TRUE;
				blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
				blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				m_deviceResources->GetD3DDevice()->CreateBlendState(&blendDesc, &m_blendState);
			}
			pX = x;
			pY = y;
			pZ = z;

			rX = rx;
			rY = ry;
			rZ = rz;

			sX = sx;
			sY = sy;
			sZ = sz;
			txNames.push_back(texture);
			txNames.push_back(texture2);
			createType = "Cube";
			
			CreateDeviceDependentResources();
			
			
			
		}
	private:
		void Rotate(float radians);
		void UpdateCamera(DX::StepTimer const& timer, float const moveSpd, float const rotSpd);

	private:

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_modelTexture;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_modelTextureTwo;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRV;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRVTwo;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

		Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

		
		bool IsTransparent = false;
		// System resources for cube geometry.
		ModelViewProjectionConstantBuffer	m_constantBufferData;
		uint32	m_indexCount;

		unsigned int modelAmount = 1;
		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;

		// Data members for keyboard and mouse input
		char	m_kbuttons[256];
		Windows::UI::Input::PointerPoint^ m_currMousePos;
		Windows::UI::Input::PointerPoint^ m_prevMousePos;

		// Matrix data member for the camera
		DirectX::XMFLOAT4X4 m_camera;
		DirectX::XMFLOAT4X4 m_Secondcamera;

		//model pos
		float pX = 0, pY = 0, pZ = 0;

		//model rotation
		float rX = 0, rY = 0, rZ = 0;
		
		//model scale
		float sX = 0, sY = 0, sZ = 0;
		std::string createType;
		std::vector<std::string> txNames;
		wchar_t * pixelShaderName = L"SamplePixelShader.cso";
		wchar_t * vertexShaderName = L"SampleVertexShader.cso";
		struct LoadedMeshStuff
		{
			std::vector<VertexPositionUVNormal> theMeshVertices;
			std::vector<std::string> textureNames;
			std::vector<unsigned short> meshIndices;
			
		};
		LoadedMeshStuff MESH;
	};
}

