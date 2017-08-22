////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: LightClass
////////////////////////////////////////////////////////////////////////////////
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetPosition(float, float, float);
	void SetPointLightDiffuseColor(float, float, float, float);
	void SetPointLightPosition(float, float, float);
	void SetSpotLightDiffuseColor(float, float, float, float);
	void SetSpotLightPosition(float, float, float);
	void SetSpotLightConeDirection(float, float, float);
	void SetSpotLightConeRatio(float);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetDirection();
	XMFLOAT3 GetPosition();
	XMFLOAT4 GetPointLightDiffuseColor();
	XMFLOAT4 GetPointLightPosition();
	XMFLOAT4 GetSpotLightDiffuseColor();
	XMFLOAT4 GetSpotLightPosition();
	XMFLOAT3 GetSpotLightConeDirection();
	float GetSpotLightConeRatio();

private:
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
	XMFLOAT3 m_position;
	XMFLOAT4 m_pointlightdiffuseColor;
	XMFLOAT4 m_pointlightPosition;
	XMFLOAT4 m_spotlightdiffuseColor;
	XMFLOAT4 m_spotlightPosition;
	XMFLOAT3 m_spotlightconeDirection;
	float m_spotlightconeRatio;
};

#endif