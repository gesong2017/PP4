////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "pointlightshaderclass.h"
#include "spotlightshaderclass.h"
#include "fontshaderclass.h"
#include "skyboxshaderclass.h"
#include "terrainshaderclass.h"
#include "castleshaderclass.h"
#include "knightshaderclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
	bool RenderPointLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4[], XMFLOAT4[]);
	bool RenderSpotLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float, XMFLOAT3, XMFLOAT4, XMFLOAT4);
	bool RenderKnightShader(ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
	bool RenderFontShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);
	bool RenderSkyboxShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
	bool RenderCastleShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT4);

private:
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	PointLightShaderClass* m_PointLightShader;
	SpotLightShaderClass* m_SpotLightShader;
	FontShaderClass* m_FontShader;
	SkyboxShaderClass* m_SkyboxShader;
	TerrainShaderClass* m_TerrainShader;
	CastleShaderClass* m_CastleShader;
	KnightShaderClass* m_KnightShader;
};

#endif