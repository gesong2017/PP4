////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, WCHAR* modelFilename, WCHAR* textureFilename)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device,modelFilename);
	if(!result)
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


void ModelClass::Shutdown()
{   
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device, WCHAR* modelFilename)
{
	//load obj file into vector
	vector<XMFLOAT3> verticesPos;
	vector<XMFLOAT2> verticesUV;
	vector<XMFLOAT3> verticesNormal;
	vector<Vertex> modelvertices;
	vector<unsigned long> modelIndices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	bool result;
	HRESULT hResult;

	result = LoadObjModel(modelFilename, verticesPos, verticesUV, verticesNormal);
	if (!result)
	{
		return false;
	}

	for (unsigned int i = 0; i < verticesPos.size(); i++)
	{
		Vertex temp;
		temp.position = verticesPos[i];
		temp.uv = verticesUV[i];
		temp.normal = verticesNormal[i];
		modelvertices.push_back(temp);
		modelIndices.push_back(i);
	}

	// Set up the description of the static vertex buffer.
	m_vertexCount = modelvertices.size();
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = &modelvertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    hResult = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(hResult))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	m_indexCount = modelIndices.size();
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = &modelIndices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	hResult = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(hResult))
	{
		return false;
	}

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadObjModel(WCHAR* fileName, vector<XMFLOAT3> &out_positions, vector<XMFLOAT2> &out_uvs, vector<XMFLOAT3> &out_normals)
{
	vector<std::string> contents;
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<XMFLOAT3> temp_positions;
	vector<XMFLOAT2> temp_uvs;
	vector<XMFLOAT3> temp_normals;
	ifstream objFile(fileName, ios::in | ios::binary);
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

		//For each uv of each triangle
		for (unsigned int i = 0; i < uvIndices.size(); i++)
		{
			unsigned int uvIndex = uvIndices[i];
			XMFLOAT2 uv = temp_uvs[uvIndex - 1];
			out_uvs.push_back(uv);
		}

		//For each normal of each triangle
		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int normalIndex = normalIndices[i];
			XMFLOAT3 normal = temp_normals[normalIndex - 1];
			out_normals.push_back(normal);
		}

		objFile.close();
		return true;
	}
	return false;
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
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

void ModelClass::ReleaseTexture()
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