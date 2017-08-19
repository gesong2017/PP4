////////////////////////////////////////////////////////////////////////////////
// Filename: skyboxclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYBOXCLASS_H_
#define _SKYBOXCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include  <DirectXMath.h>
using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: SkyboxClass
////////////////////////////////////////////////////////////////////////////////
class SkyboxClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	};

public:
	SkyboxClass();
	SkyboxClass(const SkyboxClass&);
	~SkyboxClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
};

#endif
