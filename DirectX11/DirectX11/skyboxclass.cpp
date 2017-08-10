////////////////////////////////////////////////////////////////////////////////
// Filename: skyboxclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "skyboxclass.h"

SkyboxClass::SkyboxClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}


SkyboxClass::SkyboxClass(const SkyboxClass& other)
{
}


SkyboxClass::~SkyboxClass()
{
}

bool SkyboxClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	bool result;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void SkyboxClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void SkyboxClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	return;
}

int SkyboxClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* SkyboxClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool SkyboxClass::InitializeBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// create vertices to represent the Skybox
	SkyboxVertex skyboxVertices[] =
	{
		XMFLOAT3(-1.0f, 1.0f, -1.0f),    // vertex 0
		XMFLOAT3(1.0f, 1.0f, -1.0f),    // vertex 1
		XMFLOAT3(-1.0f, -1.0f, -1.0f),    // 2
		XMFLOAT3(1.0f, -1.0f, -1.0f),    // 3
		XMFLOAT3(-1.0f, 1.0f, 1.0f),    // ...
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(-1.0f, -1.0f, 1.0f),
		XMFLOAT3(1.0f, -1.0f, 1.0f),
	};
	m_vertexCount = ARRAYSIZE(skyboxVertices);
	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(SkyboxVertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = skyboxVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// create the index buffer out of shorts
	short skyboxIndices[] =
	{
		0, 2,1,     // -z
		2, 3,1,

		4, 6,0,     // -x
		6, 2,0,

		7, 6,5,     // +z
		6, 4,5,

		3, 7,1,     // +x
		7, 5,1,

		4, 0,5,     // +y
		0, 1,5,

		3, 2,7,     // -y
		2, 6,7,
	};
	m_indexCount= ARRAYSIZE(skyboxIndices);
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(short) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = skyboxIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void SkyboxClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void SkyboxClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(SkyboxVertex);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool SkyboxClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void SkyboxClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}
