////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "zoneclass.h"

ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_Terrain = 0;
	m_Frustum = 0;
	m_Skybox = 0;
	m_Castle = 0;
	m_Knight = 0;
	terraintexture = 0;
}


ZoneClass::ZoneClass(const ZoneClass& other)
{
}


ZoneClass::~ZoneClass()
{
}


bool ZoneClass::Initialize(D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;


	// Create the user interface object.
	m_UserInterface = new UserInterfaceClass;
	if(!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, -0.5f);

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(160.0f, 30.0f, 640.0f);
	m_Position->SetRotation(0.0f, 180.0f, 0.0f);

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}

	// Initialize the frustum object.
	m_Frustum->Initialize(screenDepth);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice(), "Assets/setup.txt");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the skybox object.
	m_Skybox = new SkyboxClass;
	if (!m_Skybox)
	{
		return false;
	}

	// Initialize the skybox object.
	result = m_Skybox->Initialize(Direct3D->GetDevice(), L"Assets/SunsetSkybox.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the skybox object.", L"Error", MB_OK);
		return false;
	}

	// Create the castle object.
	m_Castle = new CastleClass;
	if (!m_Castle)
	{
		return false;
	}

	// Initialize the castle object.
	result = m_Castle->Initialize(Direct3D->GetDevice(), L"Assets/castle.obj", L"Assets/castle.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the castle object.", L"Error", MB_OK);
		return false;
	}

	// Create the knight object.
	m_Knight = new KnightClass;
	if (!m_Knight)
	{
		return false;
	}

	// Initialize the knight object.
	result = m_Knight->Initialize(Direct3D->GetDevice(), L"Assets/knight.obj", L"Assets/knight.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the knight object.", L"Error", MB_OK);
		return false;
	}

	// Set the UI to display by default.
	m_displayUI = true;

	// Set wire frame rendering initially to disabled.
	m_wireFrame = false;

	// Set the rendering of cell lines initially to disabled.
	m_cellLines = false;

	return true;
}


void ZoneClass::Shutdown()
{   
	// Release the knight object.
	if (m_Knight)
	{
		m_Knight->Shutdown();
		delete m_Knight;
		m_Knight = 0;
	}

	// Release the castle object.
	if (m_Castle)
	{
		m_Castle->Shutdown();
		delete m_Castle;
		m_Castle = 0;
	}

	// Release the skybox object.
	if (m_Skybox)
	{
		m_Skybox->Shutdown();
		delete m_Skybox;
		m_Skybox = 0;
	}

	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the user interface object.
	if(m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}


bool ZoneClass::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager, float frameTime, int fps)
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Do the frame input processing.
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ);
	if(!result)
	{
		return false;
	}

	// Do the terrain frame processing.
	m_Terrain->Frame();

	// Render the graphics.
	result = Render(Direct3D, ShaderManager, TextureManager);
	if(!result)
	{
		return false;
	}

	return true;
}


void ZoneClass::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = Input->IsDownPressed();
	m_Position->LookDownward(keyDown);

	keyDown = Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = Input->IsDPressed();
	m_Position->MoveDownward(keyDown);

	//handle the different terraintexture
	if (Input->Is1Pressed() == true)
	{
		terraintexture = 0;
	}

	else if (Input->Is2Pressed() == true)
	{
		terraintexture = 2;
	}

	else if (Input->Is3Pressed() == true)
	{
		terraintexture = 4;
	}

	else if (Input->Is4Pressed() == true)
	{
		terraintexture = 6;
	}

	else if (Input->Is5Pressed() == true)
	{
		terraintexture = 8;
	}

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if(Input->IsF1Toggled())
	{
		m_displayUI = !m_displayUI;
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if (Input->IsF2Toggled())
	{
		m_wireFrame = !m_wireFrame;
	}

	// Determine if we should render the lines around each terrain cell.
	if (Input->IsF3Toggled())
	{
		m_cellLines = !m_cellLines;
	}

	return;
}


bool ZoneClass::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	int i;
	
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);
	
	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Construct the frustum.
	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

	// Clear the buffers to begin the scene.
	Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Turn off back face culling and turn off the Z buffer.
	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	// Translate the skybox to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Render the skybox using the skybox shader.
	m_Skybox->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderSkyboxShader(Direct3D->GetDeviceContext(), m_Skybox->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Skybox->GetTexture());
	if (!result)
	{
		return false;
	}

	// Clear Z Buffer Again for the skyBox
	Direct3D->GetDeviceContext()->ClearDepthStencilView(Direct3D->GetDepthBuffer(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Reset the world matrix.
	Direct3D->GetWorldMatrix(worldMatrix);

	// Turn the Z buffer back and back face culling on.
	Direct3D->TurnZBufferOn();
	Direct3D->TurnOnCulling();

	// Render the castle using the light shader.
	XMFLOAT4X4 tempmatrix;
	XMStoreFloat4x4(&tempmatrix, worldMatrix);
	XMMATRIX castleworldmatrix;
	castleworldmatrix = XMMatrixSet(0.1f*tempmatrix._11, tempmatrix._12, tempmatrix._13, tempmatrix._14,
		                            tempmatrix._21, 0.1f*tempmatrix._22, tempmatrix._23, tempmatrix._24,
		                            tempmatrix._31, tempmatrix._32, 0.1f*tempmatrix._33, tempmatrix._34,
		                            170.0f+tempmatrix._41, 11.0f+tempmatrix._42, 435.0f+tempmatrix._43, tempmatrix._44);
	m_Castle->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderLightShader(Direct3D->GetDeviceContext(), m_Castle->GetIndexCount(), castleworldmatrix, viewMatrix,
		projectionMatrix, m_Castle->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	//cos(XMConvertToRadians(90));
	// Render the knight using the knight shader.
	XMMATRIX knightWorldMatrix;
	knightWorldMatrix = XMMatrixSet(2.0f*tempmatrix._11, tempmatrix._12, tempmatrix._13, tempmatrix._14,
		tempmatrix._21, 2.0f*tempmatrix._22, tempmatrix._23, tempmatrix._24,
		tempmatrix._31, tempmatrix._32, 2.0f*tempmatrix._33, tempmatrix._34,
		180.0f + tempmatrix._41, 9.75f + tempmatrix._42, 515.0f + tempmatrix._43, tempmatrix._44);

	knightWorldMatrix = XMMatrixMultiply(XMMatrixRotationY(380.0f), knightWorldMatrix);
	m_Knight->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderKnightShader(Direct3D->GetDeviceContext(), m_Knight->GetVertexCount(), m_Knight->GetInstanceCount(), knightWorldMatrix, viewMatrix,
		projectionMatrix, m_Castle->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame)
	{
		Direct3D->EnableWireframe();
	}

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i<m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(Direct3D->GetDeviceContext(), i, m_Frustum);
		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellIndexCount(i), worldMatrix, viewMatrix,
				projectionMatrix, TextureManager->GetTexture(terraintexture), TextureManager->GetTexture(terraintexture+1),
				m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			// If needed then render the bounding box around this terrain cell using the color shader. 
			if (m_cellLines)
			{
				m_Terrain->RenderCellLines(Direct3D->GetDeviceContext(), i);
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellLinesIndexCount(i), worldMatrix,
					viewMatrix, projectionMatrix);
				if (!result)
				{
					return false;
				}
			}
		}
	}

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame)
	{
		Direct3D->DisableWireframe();
	}

	// Update the render counts in the UI.
	result = m_UserInterface->UpdateRenderCounts(Direct3D->GetDeviceContext(), m_Terrain->GetRenderCount(), m_Terrain->GetCellsDrawn(),
		m_Terrain->GetCellsCulled());
	if (!result)
	{
		return false;
	}

	// Render the user interface.
	if(m_displayUI)
	{
		result = m_UserInterface->Render(Direct3D, ShaderManager, worldMatrix, baseViewMatrix, orthoMatrix);
		if(!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	Direct3D->EndScene();

	return true;
}