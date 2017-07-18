#pragma once

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace Platform;
using namespace DirectX;

// a struct to represent a single vertex
struct VERTEX
{
	XMFLOAT3 pos;   // vertex position
	XMFLOAT3 normal;    // color position
	XMFLOAT2 uv;
};
struct CBUFFER
{
	XMMATRIX Final;
	XMMATRIX Rotation;
	XMVECTOR DiffuseVector;
	XMVECTOR DiffuseColor;
	XMVECTOR AmbientColor;
};

class CGame
{
public:
	ComPtr<ID3D11Device1> dev;                      // the device interface
	ComPtr<ID3D11DeviceContext1> devcon;            // the device context interface
	ComPtr<IDXGISwapChain1> swapchain;              // the swap chain interface
	ComPtr<ID3D11RenderTargetView> rendertarget;    // the render target interface
	ComPtr<ID3D11Buffer> vertexbuffer;              // the vertex buffer interface
	ComPtr<ID3D11VertexShader> vertexshader;        // the vertex shader interface
	ComPtr<ID3D11PixelShader> pixelshader;          // the pixel shader interface
	ComPtr<ID3D11InputLayout> inputlayout;          // the input layout interface
	ComPtr<ID3D11Buffer> constantbuffer;            // the constant buffer interface
	ComPtr<ID3D11DepthStencilView> zbuffer;         // the depth buffer interface
	ComPtr<ID3D11Buffer> indexbuffer;               // the index buffer interface
	ComPtr<ID3D11ShaderResourceView> textureView1;       // the texture interface
	ComPtr<ID3D11ShaderResourceView> textureView2;       // the second texture view
	ComPtr<ID3D11RasterizerState> defaultrasterizerstate;     // the rasterizer state for normal rendering
	ComPtr<ID3D11RasterizerState> wireframerasterizerstate;   // the rasterizer state for wireframe
	ComPtr<ID3D11SamplerState> samplerstate[2];               // the sampler state interfaces

	//function call
	void Initialize();
	void Update();
	void Render();
	void InitGraphics();
	void InitPipeline();
	void InitWireFrameMode();
	void InitSampleStateMode();

	//additional variable
	bool Wireframe;
	bool Blurred;
	uint32	m_indexCount;
	float Time;
};