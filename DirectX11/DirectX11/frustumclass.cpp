////////////////////////////////////////////////////////////////////////////////
// Filename: frustumclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "frustumclass.h"

FrustumClass::FrustumClass()
{
}

FrustumClass::FrustumClass(const FrustumClass& other)
{
}

FrustumClass::~FrustumClass()
{
}

void FrustumClass::ConstructFrustum(float screenDepth, XMMATRIX m_projectionMatrix, XMMATRIX m_viewMatrix)
{
	float zMinimum, r;
	XMFLOAT4X4 projectionMatrix, viewMatrix;
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&projectionMatrix, m_projectionMatrix);
	XMStoreFloat4x4(&viewMatrix, m_viewMatrix);

	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	XMStoreFloat4x4(&matrix,XMMatrixMultiply(XMLoadFloat4x4(&viewMatrix), XMLoadFloat4x4(&projectionMatrix)));

	// Calculate near plane of frustum.
	m_planes[0].x = matrix._14 + matrix._13;
	m_planes[0].y = matrix._24 + matrix._23;
	m_planes[0].z = matrix._34 + matrix._33;
	m_planes[0].w = matrix._44 + matrix._43;
	XMStoreFloat4(&m_planes[0],XMPlaneNormalize(XMLoadFloat4(&m_planes[0])));

	// Calculate far plane of frustum.
	m_planes[1].x = matrix._14 - matrix._13;
	m_planes[1].y = matrix._24 - matrix._23;
	m_planes[1].z = matrix._34 - matrix._33;
	m_planes[1].w = matrix._44 - matrix._43;
	XMStoreFloat4(&m_planes[1], XMPlaneNormalize(XMLoadFloat4(&m_planes[1])));

	// Calculate left plane of frustum.
	m_planes[2].x = matrix._14 + matrix._11;
	m_planes[2].y = matrix._24 + matrix._21;
	m_planes[2].z = matrix._34 + matrix._31;
	m_planes[2].w = matrix._44 + matrix._41;
	XMStoreFloat4(&m_planes[2], XMPlaneNormalize(XMLoadFloat4(&m_planes[2])));

	// Calculate right plane of frustum.
	m_planes[3].x = matrix._14 - matrix._11;
	m_planes[3].y = matrix._24 - matrix._21;
	m_planes[3].z = matrix._34 - matrix._31;
	m_planes[3].w = matrix._44 - matrix._41;
	XMStoreFloat4(&m_planes[3], XMPlaneNormalize(XMLoadFloat4(&m_planes[3])));

	// Calculate top plane of frustum.
	m_planes[4].x = matrix._14 - matrix._12;
	m_planes[4].y = matrix._24 - matrix._22;
	m_planes[4].z = matrix._34 - matrix._32;
	m_planes[4].w = matrix._44 - matrix._42;
	XMStoreFloat4(&m_planes[4], XMPlaneNormalize(XMLoadFloat4(&m_planes[4])));

	// Calculate bottom plane of frustum.
	m_planes[5].x = matrix._14 + matrix._12;
	m_planes[5].y = matrix._24 + matrix._22;
	m_planes[5].z = matrix._34 + matrix._32;
	m_planes[5].w = matrix._44 + matrix._42;
	XMStoreFloat4(&m_planes[5], XMPlaneNormalize(XMLoadFloat4(&m_planes[5])));

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;
	XMFLOAT4 dot;

	// Check if the point is inside all six planes of the view frustum.
	for (i = 0; i<6; i++)
	{   
		XMStoreFloat4(&dot, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3(x, y, z))));
		if (dot.x < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;
	XMFLOAT4 dot1;
	XMFLOAT4 dot2;
	XMFLOAT4 dot3;
	XMFLOAT4 dot4;
	XMFLOAT4 dot5;
	XMFLOAT4 dot6;
	XMFLOAT4 dot7;
	XMFLOAT4 dot8;

	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i<6; i++)
	{   
		XMStoreFloat4(&dot1, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter - radius), (zCenter - radius)))));
		XMStoreFloat4(&dot2, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter - radius), (zCenter - radius)))));
		XMStoreFloat4(&dot3, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter + radius), (zCenter - radius)))));
		XMStoreFloat4(&dot4, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter + radius), (zCenter - radius)))));
		XMStoreFloat4(&dot5, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter - radius), (zCenter + radius)))));
		XMStoreFloat4(&dot6, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter - radius), (zCenter + radius)))));
		XMStoreFloat4(&dot7, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter + radius), (zCenter + radius)))));
		XMStoreFloat4(&dot8, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter + radius), (zCenter + radius)))));
		if (dot1.x >= 0.0f)
		{
			continue;
		}

		if (dot2.x >= 0.0f)
		{
			continue;
		}

		if (dot3.x >= 0.0f)
		{
			continue;
		}

		if (dot4.x >= 0.0f)
		{
			continue;
		}

		if (dot5.x >= 0.0f)
		{
			continue;
		}

		if (dot6.x >= 0.0f)
		{
			continue;
		}

		if (dot7.x >= 0.0f)
		{
			continue;
		}

		if (dot8.x >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;
	XMFLOAT4 dot;

	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i<6; i++)
	{   
		XMStoreFloat4(&dot, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3(xCenter, yCenter, zCenter))));
		if (dot.x < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;
	XMFLOAT4 dot1;
	XMFLOAT4 dot2;
	XMFLOAT4 dot3;
	XMFLOAT4 dot4;
	XMFLOAT4 dot5;
	XMFLOAT4 dot6;
	XMFLOAT4 dot7;
	XMFLOAT4 dot8;

	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i<6; i++)
	{   
		XMStoreFloat4(&dot1, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize)))));
		XMStoreFloat4(&dot2, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize)))));
		XMStoreFloat4(&dot3, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize)))));
		XMStoreFloat4(&dot4, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize)))));
		XMStoreFloat4(&dot5, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize)))));
		XMStoreFloat4(&dot6, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize)))));
		XMStoreFloat4(&dot7, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize)))));
		XMStoreFloat4(&dot8, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize)))));
		if (dot1.x >= 0.0f)
		{
			continue;
		}

		if (dot2.x >= 0.0f)
		{
			continue;
		}

		if (dot3.x >= 0.0f)
		{
			continue;
		}

		if (dot4.x >= 0.0f)
		{
			continue;
		}

		if (dot5.x >= 0.0f)
		{
			continue;
		}

		if (dot6.x >= 0.0f)
		{
			continue;
		}

		if (dot7.x >= 0.0f)
		{
			continue;
		}

		if (dot8.x >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}
