#include "pch.h"
#include "Game.h"
#include <fstream>
#include "DDSTextureLoader.h"
#include <vector>

// this function loads a file into an Array^
Array<byte>^ LoadShaderFile(std::string File)
{
	Array<byte>^ FileData = nullptr;

	// open the file
	std::ifstream VertexFile(File, std::ios::in | std::ios::binary | std::ios::ate);

	// if open was successful
	if (VertexFile.is_open())
	{
		// find the length of the file
		int Length = (int)VertexFile.tellg();

		// collect the file data
		FileData = ref new Array<byte>(Length);
		VertexFile.seekg(0, std::ios::beg);
		VertexFile.read(reinterpret_cast<char*>(FileData->Data), Length);
		VertexFile.close();
	}

	return FileData;
}

// this function loads a obj file into vectors
void LoadModelFile(std::string File, std::vector<XMFLOAT3> &out_positions, std::vector<XMFLOAT3> &out_normals, std::vector<XMFLOAT2> &out_uvs)
{
	std::vector<std::string> contents;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<XMFLOAT3> temp_positions;
	std::vector<XMFLOAT2> temp_uvs;
	std::vector<XMFLOAT3> temp_normals;
	std::ifstream objFile(File, std::ios::in | std::ios::binary);
	if (objFile.is_open())
	{
		//create a buffer to read current line
		char buffer[256];

		while (!objFile.eof())
		{
			objFile.getline(buffer, 256);
			contents.push_back(std::string(buffer));
		}
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			//check if it's a comment or not
			if (contents[i].c_str()[0] == '#')
				continue;

			// check if it's a valid vertex position
			else if (contents[i].c_str()[0] == 'v' && contents[i].c_str()[1] == ' ')
			{
				XMFLOAT3 tempPos;
				sscanf_s(contents[i].c_str(), "v %f %f %f", &tempPos.x, &tempPos.y, &tempPos.z);
				temp_positions.push_back(tempPos);
			}

			// check if it's a valid texture coordinate
			else if (contents[i].c_str()[0] == 'v' && contents[i].c_str()[1] == 't' &&contents[i].c_str()[2] == ' ')
			{
				XMFLOAT2 tempUV;
				sscanf_s(contents[i].c_str(), "vt %f %f", &tempUV.x, &tempUV.y);
				temp_uvs.push_back(tempUV);
			}

			//check if it's a valid normal
			else if (contents[i].c_str()[0] == 'v' && contents[i].c_str()[1] == 'n' &&contents[i].c_str()[2] == ' ')
			{
				XMFLOAT3 tempNormal;
				sscanf_s(contents[i].c_str(), "vn %f %f %f", &tempNormal.x, &tempNormal.y, &tempNormal.z);
				temp_normals.push_back(tempNormal);
			}

			//check if it's a valid face
			else if (contents[i].c_str()[0] == 'f' && contents[i].c_str()[1] == ' ')
			{
				unsigned int positionIndex[3], uvIndex[3], normalIndex[3];
				sscanf_s(contents[i].c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i",
					&positionIndex[0], &uvIndex[0], &normalIndex[0],
					&positionIndex[1], &uvIndex[1], &normalIndex[1],
					&positionIndex[2], &uvIndex[2], &normalIndex[2]
				);
				vertexIndices.push_back(positionIndex[0]);
				vertexIndices.push_back(positionIndex[1]);
				vertexIndices.push_back(positionIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			XMFLOAT3 vertexPos = temp_positions[vertexIndex - 1];
			out_positions.push_back(vertexPos);
		}

		//For each normal of each triangle
		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int normalIndex = normalIndices[i];
			XMFLOAT3 normal = temp_normals[normalIndex - 1];
			out_normals.push_back(normal);
		}

		//For each uv of each triangle
		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int uvIndex = uvIndices[i];
			XMFLOAT2 uv = temp_uvs[uvIndex - 1];
			out_uvs.push_back(uv);
		}
		objFile.close();
	}

}


// this function initializes and prepares Direct3D for use
void CGame::Initialize()
{
	// Define temporary pointers to a device and a device context
	ComPtr<ID3D11Device> dev11;
	ComPtr<ID3D11DeviceContext> devcon11;

	// Create the device and device context objects
	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&dev11,
		nullptr,
		&devcon11);

	// Convert the pointers from the DirectX 11 versions to the DirectX 11.1 versions
	dev11.As(&dev);
	devcon11.As(&devcon);


	// obtain the DXGI factory
	ComPtr<IDXGIDevice1> dxgiDevice;
	dev.As(&dxgiDevice);
	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);
	ComPtr<IDXGIFactory2> dxgiFactory;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

	// set up the swap chain description
	DXGI_SWAP_CHAIN_DESC1 scd = { 0 };
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // how the swap chain should be used
	scd.BufferCount = 2;                                  // a front buffer and a back buffer
	scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;              // the most common swap chain format
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;    // the recommended flip mode
	scd.SampleDesc.Count = 1;                             // disable anti-aliasing

	CoreWindow^ Window = CoreWindow::GetForCurrentThread();    // get the window pointer

															   // create the swap chain
	dxgiFactory->CreateSwapChainForCoreWindow(
		dev.Get(),                                  // address of the device
		reinterpret_cast<IUnknown*>(Window),        // address of the window
		&scd,                                       // address of the swap chain description
		nullptr,                                    // advanced
		&swapchain);                                // address of the new swap chain pointer


													// get a pointer directly to the back buffer
	ComPtr<ID3D11Texture2D> backbuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backbuffer);

	// create a render target pointing to the back buffer
	dev->CreateRenderTargetView(backbuffer.Get(), nullptr, &rendertarget);


	// create a zbuffer
	D3D11_TEXTURE2D_DESC texd = { 0 };

	texd.Width = (UINT)Window->Bounds.Width;
	texd.Height = (UINT)Window->Bounds.Height;
	texd.ArraySize = 1;
	texd.MipLevels = 1;
	texd.SampleDesc.Count = 1;
	texd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ComPtr<ID3D11Texture2D> zbuffertexture;
	dev->CreateTexture2D(&texd, nullptr, &zbuffertexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));

	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	dev->CreateDepthStencilView(zbuffertexture.Get(), &dsvd, &zbuffer);


	// set the viewport
	D3D11_VIEWPORT viewport = { 0 };

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Window->Bounds.Width;
	viewport.Height = Window->Bounds.Height;
	viewport.MinDepth = 0;    // the closest an object can be on the depth buffer is 0.0
	viewport.MaxDepth = 1;    // the farthest an object can be on the depth buffer is 1.0

	devcon->RSSetViewports(1, &viewport);


	// initialize graphics and the pipeline
	InitGraphics();
	InitPipeline();
	//InitWireFrameMode();
	//InitSampleStateMode();

	// initialize variables
	Time = 0.0f;
	Wireframe = false;
}

// this function performs updates to the state of the game
void CGame::Update()
{
	Time += 0.02f;
	//if ((int)Time % 2 == 0) 
	//	Wireframe = true;
	//else 
	//	Wireframe = false;
	//if ((int)Time % 2 == 0) 
	//	Blurred = true;
 //   else 
	//	Blurred = false;

	// calculate the world matrices
	XMMATRIX worldMatrix = XMMatrixRotationY(Time);
	XMStoreFloat4x4(&constantBufferData.worldMatrix, worldMatrix);
}

// this function renders a single frame of 3D graphics
void CGame::Render()
{
	// set our new render target object as the active render target
	devcon->OMSetRenderTargets(1, rendertarget.GetAddressOf(), zbuffer.Get());

	// clear the back buffer to a deep blue
	float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	devcon->ClearRenderTargetView(rendertarget.Get(), color);

	// clear the depth buffer
	devcon->ClearDepthStencilView(zbuffer.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	// set the vertex buffer and index buffer
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);
	devcon->IASetIndexBuffer(indexbuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// set the primitive topology
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//set the constant buffer
	devcon->VSSetConstantBuffers(0, 1, constantbuffer.GetAddressOf());

	//set the input layout
	devcon->IASetInputLayout(inputlayout.Get());

	// set the shader objects as the active shaders
	devcon->VSSetShader(vertexshader.Get(), nullptr, 0);
	devcon->PSSetShader(pixelshader.Get(), nullptr, 0);

	// send the constant buffer data to video memory
	devcon->UpdateSubresource(constantbuffer.Get(), 0, 0, &constantBufferData, 0, 0);

	// tell the GPU which texture to use
	devcon->PSSetShaderResources(0, 1, textureView1.GetAddressOf());
	//devcon->PSSetShaderResources(1, 1, textureView2.GetAddressOf());

	// set the appropriate sampler state
	if (Blurred)
		devcon->PSSetSamplers(0, 1, samplerstate[0].GetAddressOf());
	else
		devcon->PSSetSamplers(0, 1, samplerstate[1].GetAddressOf());

	// set the appropriate rasterizer state
	if (Wireframe)
		devcon->RSSetState(wireframerasterizerstate.Get());
	else
		devcon->RSSetState(defaultrasterizerstate.Get());

	// draw the Hypercraft
	devcon->DrawIndexed(m_indexCount, 0, 0);

	// switch the back buffer and the front buffer
	swapchain->Present(1, 0);
}

// this function loads and initializes all graphics data
void CGame::InitGraphics()
{    
	//load obj file into vector
	std::vector<XMFLOAT3> verticesPos;
	std::vector<XMFLOAT3> verticesNormal;
	std::vector<XMFLOAT2> verticesUV;
	LoadModelFile("Assets/talon.obj", verticesPos, verticesNormal, verticesUV);
	std::vector<VERTEX> modelvertices;
	std::vector<short> modelIndices;
	for (unsigned int i = 0; i < verticesPos.size(); i++)
	{
		VERTEX temp;
		temp.pos = verticesPos[i];
		temp.normal = verticesNormal[i];
		temp.uv = verticesUV[i];
		modelvertices.push_back(temp);
		modelIndices.push_back(i);
	}

	// create the vertex buffer
	D3D11_BUFFER_DESC bd = { 0 };
	bd.ByteWidth = sizeof(VERTEX) * modelvertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA srd = { &modelvertices[0], 0, 0 };

	dev->CreateBuffer(&bd, &srd, &vertexbuffer);

	//create the index buffer
	m_indexCount = modelIndices.size();
	D3D11_BUFFER_DESC ibd = { 0 };
	ibd.ByteWidth = sizeof(short) * modelIndices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA isrd = { &modelIndices[0], 0, 0 };

	dev->CreateBuffer(&ibd, &isrd, &indexbuffer);

	// load the first texture
	HRESULT hr = CreateDDSTextureFromFile
	(
		dev.Get(),
		L"Assets/talon.dds",
		nullptr,
		&textureView1,
		0
	);

	// load the second texture
	//hr= CreateDDSTextureFromFile
	//(
	//	dev.Get(),
	//	L"Assets/texture2.dds",
	//	nullptr,
	//	&textureView2,
	//	0
	//);

	// calculate the view transformation
	static const XMVECTORF32 eye = { 0.0f, 3.0f, -5.0f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };
	XMStoreFloat4x4(&constantBufferData.viewMatrix, XMMatrixLookAtLH(eye, at, up));

	// calculate the projection transformation
	CoreWindow^ Window = CoreWindow::GetForCurrentThread();    // get the window pointer
	XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45),                                      // the field of view
		(FLOAT)Window->Bounds.Width / (FLOAT)Window->Bounds.Height,  // aspect ratio
		0.1f,                                                           // the near view-plane
		100.0f);                                                        // the far view-plane

	XMStoreFloat4x4(&constantBufferData.projectionMatrix, projectionMatrix);

	//light stuff for constant buffer
	constantBufferData.DiffuseVector = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
	constantBufferData.DiffuseColor = XMVectorSet(0.7f, 0.7f, 0.7f, 1.0f);
	constantBufferData.AmbientColor = XMVectorSet(0.2f, 0.2f, 0.2f, 1.0f);
}

// this function initializes the GPU settings and prepares it for rendering
void CGame::InitPipeline()
{
	// load the shader files
	Array<byte>^ VSFile = LoadShaderFile("VertexShader.cso");
	Array<byte>^ PSFile = LoadShaderFile("PixelShader.cso");

	// create the shader objects
	dev->CreateVertexShader(VSFile->Data, VSFile->Length, nullptr, &vertexshader);
	dev->CreatePixelShader(PSFile->Data, PSFile->Length, nullptr, &pixelshader);



	// initialize input layout
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// create the input layout
	dev->CreateInputLayout(ied, ARRAYSIZE(ied), VSFile->Data, VSFile->Length, &inputlayout);

	// define the constant buffer
	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WorldViewProjectionConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&bd, nullptr, &constantbuffer);
}

// this function initializes the WireFrameMode states
void CGame::InitWireFrameMode()
{
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = FALSE;
	rd.DepthClipEnable = TRUE;
	rd.ScissorEnable = FALSE;
	rd.AntialiasedLineEnable = FALSE;
	rd.MultisampleEnable = FALSE;
	rd.DepthBias = 0;
	rd.DepthBiasClamp = 0.0f;
	rd.SlopeScaledDepthBias = 0.0f;

	dev->CreateRasterizerState(&rd, &defaultrasterizerstate);

	// set the changed values for wireframe mode
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.AntialiasedLineEnable = TRUE;

	dev->CreateRasterizerState(&rd, &wireframerasterizerstate);
}

// this function initializes the SampleStateMode states
void CGame::InitSampleStateMode()
{
	D3D11_SAMPLER_DESC sd;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;
	sd.MaxAnisotropy = 16;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.BorderColor[0] = 0.0f;
	sd.BorderColor[1] = 0.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 0.0f;
	sd.MinLOD = 0.0f;
	sd.MaxLOD = FLT_MAX;
	sd.MipLODBias = 0.0f;

	dev->CreateSamplerState(&sd, &samplerstate[0]);    // create the anisotropic sampler

	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;       // linear filtering
	sd.MinLOD = 5.0f;                                  // mip level 5 will appear blurred

	dev->CreateSamplerState(&sd, &samplerstate[1]);    // create the linear blur sampler
}