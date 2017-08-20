////////////////////////////////////////////////////////////////////////////////
// Filename: dragonclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DRAGONCLASS_H_
#define _DRAGONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "textureclass.h"
using namespace DirectX;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: DragonClass
////////////////////////////////////////////////////////////////////////////////
class DragonClass
{
private:
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT2 uv;
		XMFLOAT3 normal;
	};

public:
	DragonClass();
	DragonClass(const DragonClass&);
	~DragonClass();

	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*, WCHAR*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadObjModel(WCHAR* fileName, vector<XMFLOAT3> &out_position, vector<XMFLOAT2> &out_uv, vector<XMFLOAT3> &out_normal);
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
};

#endif
