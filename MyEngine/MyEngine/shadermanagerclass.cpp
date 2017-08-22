////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "shadermanagerclass.h"

ShaderManagerClass::ShaderManagerClass()
{
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_PointLightShader = 0;
	m_SpotLightShader = 0;
	m_FontShader = 0;
	m_SkyboxShader = 0;
	m_TerrainShader = 0;
	m_CastleShader = 0;
	m_KnightShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(device, hwnd);
	if(!result)
	{
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the Point light shader object.
	m_PointLightShader = new PointLightShaderClass;
	if (!m_PointLightShader)
	{
		return false;
	}

	// Initialize the point light shader object.
	result = m_PointLightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the spot light shader object.
	m_SpotLightShader = new SpotLightShaderClass;
	if (!m_SpotLightShader)
	{
		return false;
	}

	// Initialize the spot light shader object.
	result = m_SpotLightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if(!result)
	{
		return false;
	}

	// Create the skybox shader object.
	m_SkyboxShader = new SkyboxShaderClass;
	if (!m_SkyboxShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_SkyboxShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the castle shader object.
	m_CastleShader = new CastleShaderClass;
	if (!m_CastleShader)
	{
		return false;
	}

	// Initialize the castle shader object.
	result = m_CastleShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the Knight shader object.
	m_KnightShader = new KnightShaderClass;
	if (!m_KnightShader)
	{
		return false;
	}

	// Initialize the knight shader object.
	result = m_KnightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}


void ShaderManagerClass::Shutdown()
{   
	// Release the castle shader object.
	if (m_CastleShader)
	{
		m_CastleShader->Shutdown();
		delete m_CastleShader;
		m_CastleShader = 0;
	}

	// Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the skybox shader object.
	if (m_SkyboxShader)
	{
		m_SkyboxShader->Shutdown();
		delete m_SkyboxShader;
		m_SkyboxShader = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the knight shader object.
	if (m_KnightShader)
	{
		m_KnightShader->Shutdown();
		delete m_KnightShader;
		m_KnightShader = 0;
	}

	// Release the spot light shader object.
	if (m_SpotLightShader)
	{
		m_SpotLightShader->Shutdown();
		delete m_SpotLightShader;
		m_SpotLightShader = 0;
	}

	// Release the point light shader object.
	if (m_PointLightShader)
	{
		m_PointLightShader->Shutdown();
		delete m_PointLightShader;
		m_PointLightShader = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	return;
}


bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, 
										   XMMATRIX projectionMatrix)
{
	return m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	return m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	return m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuseColor);
}

bool ShaderManagerClass::RenderPointLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 diffuseColor[], XMFLOAT4 lightPosition[])
{
	return m_PointLightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPosition);
}

bool ShaderManagerClass::RenderSpotLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float coneRatio, XMFLOAT3 lightConeDirection,
	XMFLOAT4 diffuseColor, XMFLOAT4 lightPosition)
{
	return m_SpotLightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, coneRatio, lightConeDirection, diffuseColor, lightPosition);
}

bool ShaderManagerClass::RenderKnightShader(ID3D11DeviceContext* deviceContext, int vertexCount, int instanceCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	return m_KnightShader->Render(deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuseColor);
}

bool ShaderManagerClass::RenderFontShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, 
										  XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 color)
{
	return m_FontShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, color);
}

bool ShaderManagerClass::RenderSkyboxShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	return m_SkyboxShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManagerClass::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* normalMap, XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	return m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, normalMap, lightDirection, diffuseColor);
}

bool ShaderManagerClass::RenderCastleShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT3 dlightDirection, XMFLOAT4 dlightdiffuseColor, XMFLOAT4 plightdiffuseColor, XMFLOAT4 plightPosition)
{
	return m_CastleShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, dlightDirection, dlightdiffuseColor, plightdiffuseColor, plightPosition);
}