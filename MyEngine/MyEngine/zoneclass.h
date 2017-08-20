////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ZONECLASS_H_
#define _ZONECLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <math.h>
#include "d3dclass.h"
#include "inputclass.h"
#include "shadermanagerclass.h"
#include "texturemanagerclass.h"
#include "timerclass.h"
#include "userinterfaceclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "positionclass.h"
#include "terrainclass.h"
#include "frustumclass.h"
#include "skyboxclass.h"
#include "castleclass.h"
#include "knightclass.h"
#include "dragonclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ZoneClass
////////////////////////////////////////////////////////////////////////////////
class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass&);
	~ZoneClass();

	bool Initialize(D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, TextureManagerClass*, float, int);

private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*, TextureManagerClass*);

private:
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	LightClass* m_Light, *m_PointLight1, *m_PointLight2, *m_PointLight3, *m_PointLight4;
	PositionClass* m_Position;
	FrustumClass* m_Frustum;
	TerrainClass* m_Terrain;
	SkyboxClass* m_Skybox;
	CastleClass* m_Castle;
	KnightClass* m_Knight;
	DragonClass* m_Dragon;
	bool m_displayUI, m_wireFrame, m_cellLines;
	unsigned int terraintexture;
};

#endif