////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "zoneclass.h"

ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_PointLight1 = 0;
	m_PointLight2 = 0;
	m_PointLight3 = 0;
	m_PointLight4 = 0;
	m_SpotLight = 0;
	m_Position = 0;
	m_RenderTexture = 0;
	m_DebugWindow = 0;
	m_Terrain = 0;
	m_Frustum = 0;
	m_Skybox = 0;
	m_Castle = 0;
	m_Knight = 0;
	m_Dragon = 0;
	m_Tower = 0;
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

	// Create the point light1 object.
	m_PointLight1 = new LightClass;
	if (!m_PointLight1)
	{
		return false;
	}

	// Initialize the point light1 object.
	m_PointLight1->SetPointLightDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_PointLight1->SetPointLightPosition(-300.0f, 200.0f, 300.0f);

	// Create the point light2 object.
	m_PointLight2 = new LightClass;
	if (!m_PointLight2)
	{
		return false;
	}

	// Initialize the point light2 object.
	m_PointLight2->SetPointLightDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_PointLight2->SetPointLightPosition(300.0f, 200.0f, 300.0f);

	// Create the point light3 object.
	m_PointLight3 = new LightClass;
	if (!m_PointLight3)
	{
		return false;
	}

	// Initialize the point light3 object.
	m_PointLight3->SetPointLightDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_PointLight3->SetPointLightPosition(-300.0f, 100.0f, 300.0f);

	// Create the point light4 object.
	m_PointLight4 = new LightClass;
	if (!m_PointLight4)
	{
		return false;
	}

	// Initialize the point light4 object.
	m_PointLight4->SetPointLightDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_PointLight4->SetPointLightPosition(300.0f, 100.0f, 300.0f);

	// Create the spot light object.
	m_SpotLight = new LightClass;
	if (!m_SpotLight)
	{
		return false;
	}

	// Initialize the spot light object.
	m_SpotLight->SetSpotLightDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	m_SpotLight->SetSpotLightPosition(300.0f, 50.0f, -300.0f);
	m_SpotLight->SetSpotLightConeDirection(1.0f, 1.0f, 1.0f);
	m_SpotLight->SetSpotLightConeRatio(0.2f);

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(160.0f, 30.0f, 640.0f);
	m_Position->SetRotation(0.0f, 180.0f, 0.0f);

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Create the debug window object.
	m_DebugWindow = new DebugWindowClass;
	if (!m_DebugWindow)
	{
		return false;
	}

	// Initialize the debug window object.
	result = m_DebugWindow->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight, screenWidth/8, screenHeight/8);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

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

	// Create the dragon object.
	m_Dragon = new DragonClass;
	if (!m_Dragon)
	{
		return false;
	}

	// Initialize the dragon object.
	result = m_Dragon->Initialize(Direct3D->GetDevice(), L"Assets/dragon.obj", L"Assets/dragon.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dragon object.", L"Error", MB_OK);
		return false;
	}

	// Create the tower object.
	m_Tower = new TowerClass;
	if (!m_Tower)
	{
		return false;
	}

	// Initialize the tower object.
	result = m_Tower->Initialize(Direct3D->GetDevice(), L"Assets/tower.obj", L"Assets/tower.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the tower object.", L"Error", MB_OK);
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
	// Release the tower object.
	if (m_Tower)
	{
		m_Tower->Shutdown();
		delete m_Tower;
		m_Tower = 0;
	}

	// Release the dragon object.
	if (m_Dragon)
	{
		m_Dragon->Shutdown();
		delete m_Dragon;
		m_Dragon = 0;
	}

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

	// Release the debug window object.
	if (m_DebugWindow)
	{
		m_DebugWindow->Shutdown();
		delete m_DebugWindow;
		m_DebugWindow = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the spot light object.
	if (m_SpotLight)
	{
		delete m_SpotLight;
		m_SpotLight = 0;
	}

	// Release the point light4 object.
	if (m_PointLight4)
	{
		delete m_PointLight4;
		m_PointLight4 = 0;
	}

	// Release the point light3 object.
	if (m_PointLight3)
	{
		delete m_PointLight3;
		m_PointLight3 = 0;
	}

	// Release the point light2 object.
	if (m_PointLight2)
	{
		delete m_PointLight2;
		m_PointLight2 = 0;
	}

	// Release the point light1 object.
	if (m_PointLight1)
	{
		delete m_PointLight1;
		m_PointLight1 = 0;
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

	// initialize random seed: 
	srand(time(NULL));

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

	//handle the random light
	if (Input->Is1Pressed() == true)
	{
		m_Light->SetDirection(rand() % 4 - 1.5f, rand() % 3 - 1.0f, rand() % 2 - 0.5f);
	}

	else if (Input->Is2Pressed() == true)
	{
		m_PointLight1->SetPointLightPosition(rand() % 601 - 300.0f, rand() % 601 - 300.0f, rand() % 601 - 300.0f);
		m_PointLight2->SetPointLightPosition(rand() % 601 - 300.0f, rand() % 601 - 300.0f, rand() % 601 - 300.0f);
		m_PointLight3->SetPointLightPosition(rand() % 601 - 300.0f, rand() % 601 - 300.0f, rand() % 601 - 300.0f);
		m_PointLight4->SetPointLightPosition(rand() % 601 - 300.0f, rand() % 601 - 300.0f, rand() % 601 - 300.0f);
	}

	else if (Input->Is3Pressed() == true)
	{
		m_SpotLight->SetSpotLightPosition(rand() % 601 - 300.0f, rand() % 601 - 300.0f, -300.0f);
		m_SpotLight->SetSpotLightConeDirection(rand() % 3 - 1.0f, rand() % 3 - 1.0f, rand() % 3 - 1.0f);
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
	XMFLOAT4 pointlightdiffuseColor[4];
	XMFLOAT4 pointlightPosition[4];
	XMFLOAT3 cameraPosition;
	int i;
	
	// Create the diffuse color array from the four light colors.
	pointlightdiffuseColor[0] = m_PointLight1->GetPointLightDiffuseColor();
	pointlightdiffuseColor[1] = m_PointLight2->GetPointLightDiffuseColor();
	pointlightdiffuseColor[2] = m_PointLight3->GetPointLightDiffuseColor();
	pointlightdiffuseColor[3] = m_PointLight4->GetPointLightDiffuseColor();

	// Create the light position array from the four light positions.
	pointlightPosition[0] = m_PointLight1->GetPointLightPosition();
	pointlightPosition[1] = m_PointLight2->GetPointLightPosition();
	pointlightPosition[2] = m_PointLight3->GetPointLightPosition();
	pointlightPosition[3] = m_PointLight4->GetPointLightPosition();

	// Render the entire scene to the texture first.
	result = RenderToTexture(Direct3D, ShaderManager, TextureManager);
	if (!result)
	{
		return false;
	}

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

	// Turn the Z buffer back and back face culling on.
	Direct3D->TurnZBufferOn();
	Direct3D->TurnOnCulling();

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

	// Render the castle using the castle shader.
	XMFLOAT4X4 tempmatrix;
	XMStoreFloat4x4(&tempmatrix, worldMatrix);
	XMMATRIX castleworldmatrix;
	castleworldmatrix = XMMatrixSet(0.1f*tempmatrix._11, tempmatrix._12, tempmatrix._13, tempmatrix._14,
		                            tempmatrix._21, 0.1f*tempmatrix._22, tempmatrix._23, tempmatrix._24,
		                            tempmatrix._31, tempmatrix._32, 0.1f*tempmatrix._33, tempmatrix._34,
		                            170.0f+tempmatrix._41, 11.0f+tempmatrix._42, 435.0f+tempmatrix._43, tempmatrix._44);
	m_Castle->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderCastleShader(Direct3D->GetDeviceContext(), m_Castle->GetIndexCount(), castleworldmatrix, viewMatrix,
		projectionMatrix, m_Castle->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), pointlightdiffuseColor[0], pointlightPosition[0]);
	if (!result)
	{
		return false;
	}

	// Render the dragon using the point light shader.
	XMMATRIX dragonWorldMatrix;
	dragonWorldMatrix = XMMatrixSet(2.0f*tempmatrix._11, tempmatrix._12, tempmatrix._13, tempmatrix._14,
		tempmatrix._21, 2.0f*tempmatrix._22, tempmatrix._23, tempmatrix._24,
		tempmatrix._31, tempmatrix._32, 2.0f*tempmatrix._33, tempmatrix._34,
		220.0f + tempmatrix._41, 180.0f + tempmatrix._42, -110.0f + tempmatrix._43, tempmatrix._44);
	dragonWorldMatrix = XMMatrixMultiply(XMMatrixRotationY(380.0f), dragonWorldMatrix);
	m_Dragon->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderPointLightShader(Direct3D->GetDeviceContext(), m_Castle->GetIndexCount(), dragonWorldMatrix, viewMatrix,
		projectionMatrix, m_Dragon->GetTexture(), pointlightdiffuseColor, pointlightPosition);
	if (!result)
	{
		return false;
	}

	// Render the tower using the tower shader.
	XMMATRIX towerWorldMatrix;
	towerWorldMatrix = XMMatrixSet(0.1f*tempmatrix._11, tempmatrix._12, tempmatrix._13, tempmatrix._14,
		tempmatrix._21, 0.1f*tempmatrix._22, tempmatrix._23, tempmatrix._24,
		tempmatrix._31, tempmatrix._32, 0.1f*tempmatrix._33, tempmatrix._34,
		250.0f + tempmatrix._41, 8.0f + tempmatrix._42, 570.0f + tempmatrix._43, tempmatrix._44);

	m_Tower->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderSpotLightShader(Direct3D->GetDeviceContext(), m_Tower->GetIndexCount(), towerWorldMatrix, viewMatrix,
		projectionMatrix, m_Tower->GetTexture(), m_SpotLight->GetSpotLightConeRatio(), m_SpotLight->GetSpotLightConeDirection(),
		m_SpotLight->GetSpotLightDiffuseColor(), m_SpotLight->GetSpotLightPosition());
	if (!result)
	{
		return false;
	}

	// Render the knight using the knight shader.
	XMMATRIX knightWorldMatrix;
	knightWorldMatrix = XMMatrixSet(2.0f*tempmatrix._11, tempmatrix._12, tempmatrix._13, tempmatrix._14,
		tempmatrix._21, 2.0f*tempmatrix._22, tempmatrix._23, tempmatrix._24,
		tempmatrix._31, tempmatrix._32, 2.0f*tempmatrix._33, tempmatrix._34,
		180.0f + tempmatrix._41, 9.75f + tempmatrix._42, 515.0f + tempmatrix._43, tempmatrix._44);

	knightWorldMatrix = XMMatrixMultiply(XMMatrixRotationY(380.0f), knightWorldMatrix);
	m_Knight->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderKnightShader(Direct3D->GetDeviceContext(), m_Knight->GetVertexCount(), m_Knight->GetInstanceCount(), knightWorldMatrix, viewMatrix,
		projectionMatrix, m_Knight->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
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
				projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
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

	// Turn off back face culling and turn off the Z buffer.
	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	// Render the debugwindow using the texture shader.
	m_DebugWindow->Render(Direct3D->GetDeviceContext(), 1000, 50);
	result = ShaderManager->RenderTextureShader(Direct3D->GetDeviceContext(), m_DebugWindow->GetIndexCount(), worldMatrix, baseViewMatrix,
		orthoMatrix, m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
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

bool ZoneClass::RenderToTexture(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{   
	bool result;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(Direct3D->GetDeviceContext(), Direct3D->GetDepthBuffer());

    // Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(Direct3D->GetDeviceContext(), Direct3D->GetDepthBuffer(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderScene(Direct3D, ShaderManager, TextureManager);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	Direct3D->SetBackBufferRenderTarget();
	
	return true;
}

bool ZoneClass::RenderScene(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{   
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;
	int i;

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i<m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(Direct3D->GetDeviceContext(), i, m_Frustum);
		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellIndexCount(i), worldMatrix, viewMatrix,
				projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
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

	return true;
}

