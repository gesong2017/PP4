////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightclass.h"

LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}


void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}


void LightClass::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
	return;
}

void LightClass::SetPointLightDiffuseColor(float red, float green, float blue, float alpha)
{
	m_pointlightdiffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::SetPointLightPosition(float x, float y, float z)
{
	m_pointlightPosition = XMFLOAT4(x, y, z, 1.0f);
	return;
}

XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}


XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}


XMFLOAT3 LightClass::GetPosition()
{
	return m_position;
}

XMFLOAT4 LightClass::GetPointLightDiffuseColor()
{
	return m_pointlightdiffuseColor;
}

XMFLOAT4 LightClass::GetPointLightPosition()
{
	return m_pointlightPosition;
}

