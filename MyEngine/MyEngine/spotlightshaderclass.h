#ifndef _SPOTLIGHTSHADERCLASS_H_
#define _SPOTLIGHTSHADERCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: SpotLightShaderClass
////////////////////////////////////////////////////////////////////////////////
class SpotLightShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightColorBufferType
	{
		XMFLOAT4 diffuseColor;
	};

	struct LightPositionBufferType
	{
		XMFLOAT4 lightPosition;
	};

	struct LightConeBufferType
	{
		XMFLOAT3 coneDirection;
		float coneRatio;
	};

public:
	SpotLightShaderClass();
	SpotLightShaderClass(const SpotLightShaderClass&);
	~SpotLightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float, XMFLOAT3, XMFLOAT4, XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float, XMFLOAT3, XMFLOAT4, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightColorBuffer;
	ID3D11Buffer* m_lightPositionBuffer;
	ID3D11Buffer* m_lightConeBuffer;
};

#endif
