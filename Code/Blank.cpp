//-----------------------------------------------------------------------------
// Demonstration of Directional Lighting in Direct3D

#define D3D_DEBUG_INFO

//-----------------------------------------------------------------------------
// Include these files
#include <Windows.h>	// Windows library (for window functions, menus, dialog boxes, etc)
#include <vector>
#include <memory>
#include "PatternCreator.h"

//-----------------------------------------------------------------------------
// Global variables

LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // The rendering device


//basic buffers
LPDIRECT3DVERTEXBUFFER9 pTopBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pBottomBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pFrontBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pLeftBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pRightBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pBackBuffer = NULL; // Buffer to hold vertices of basic block
LPDIRECT3DVERTEXBUFFER9 pStudBuffer = NULL; // Buffer to hold vertices of basic block


std::vector<std::shared_ptr<LegoBlock>> g_Blocks;
D3DXVECTOR3 g_vCamera(25.0f, 25.0f, -20.0f);
D3DXVECTOR3 g_vLookat(10.0f, 5.0f, 10.0f);

// The structure of a vertex in our vertex buffer...
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

//-----------------------------------------------------------------------------
// Initialise Direct 3D.
// Requires a handle to the window in which the graphics will be drawn.
HRESULT SetupD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Enable the Z buffer, since we're dealing with 3D geometry.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// Enable culling.
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);


	return S_OK;
}

//-----------------------------------------------------------------------------
// Release (delete) all the resources used by this program.
// Only release things if they are valid (i.e. have a valid pointer).
// If not, the program will crash at this point.
void CleanUp()
{

	if (pTopBuffer != NULL)					pTopBuffer->Release();
	if (pBottomBuffer != NULL)				pBottomBuffer->Release();
	if (pFrontBuffer != NULL)				pFrontBuffer->Release();
	if (pLeftBuffer != NULL)				pLeftBuffer->Release();
	if (pRightBuffer != NULL)				pRightBuffer->Release();
	if (pBackBuffer != NULL)				pBackBuffer->Release();
	if (pStudBuffer != NULL)					pStudBuffer->Release();


	if (g_pd3dDevice != NULL)				g_pd3dDevice->Release();
	if (g_pD3D != NULL)						g_pD3D->Release();
}

void SetupLegos()
{
	/*std::shared_ptr<LegoBlock> a(new LegoBlock(0, 0, 0, Utils::Green));
	g_Blocks.push_back(a);

	std::shared_ptr<LegoBlock> b(new LegoBlock(1, 0, 0, Utils::Green));
	g_Blocks.push_back(b);

	std::shared_ptr<LegoBlock> c(new LegoBlock(2, 0, 0, Utils::Green));
	g_Blocks.push_back(c);

	std::shared_ptr<LegoBlock> d(new LegoBlock(1, 0, 1, Utils::Green));
	g_Blocks.push_back(d);*/

	//create the world
	//outer grass
	PatternCreator::AddUniformAmount(g_Blocks, 5, 1, 30, 0, 0, 0, Col_DarkGreen);
	PatternCreator::AddUniformAmount(g_Blocks, 5, 1, 30, 25, 0, 0, Col_DarkGreen);
	PatternCreator::AddUniformAmount(g_Blocks, 20, 1, 5, 5, 0, 0, Col_DarkGreen);
	PatternCreator::AddUniformAmount(g_Blocks, 20, 1, 5, 5, 0, 25, Col_DarkGreen);

	//road
	PatternCreator::AddUniformAmount(g_Blocks, 3, 1, 20, 5, 0, 5, Col_DarkGrey);
	PatternCreator::AddUniformAmount(g_Blocks, 3, 1, 20, 22, 0, 5, Col_DarkGrey);
	PatternCreator::AddUniformAmount(g_Blocks, 14, 1, 3, 8, 0, 5, Col_DarkGrey);
	PatternCreator::AddUniformAmount(g_Blocks, 14, 1, 3, 8, 0, 22, Col_DarkGrey);

	//center grass and house
	PatternCreator::AddUniformAmount(g_Blocks, 14, 1, 14, 8, 0, 8, Col_DarkGreen);
	PatternCreator::AddUniformAmount(g_Blocks, 3, 2, 4, 10, 1, 10, Col_BrightRed);

	////create moving block
	//std::shared_ptr<LegoBlock> b(new LegoBlock(6, 1, 6, Utils::Red));
	//g_Blocks.push_back(b);

	for (std::shared_ptr<LegoBlock> &b : g_Blocks)
	{
		b->SetCovereds(g_Blocks);
	}
}

//-----------------------------------------------------------------------------
// Set up the scene geometry.
// Define a cube, with associated vertex normals.
HRESULT SetupGeometry()
{
	void SetupVertexWithNormalGeometry(CUSTOMVERTEX* pV, int index,
		float px, float py, float pz,
		float nx, float ny, float nz);

	int BufferSize = 6 * sizeof(CUSTOMVERTEX);
	CUSTOMVERTEX *pVertices;

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pFrontBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pFrontBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}
	// Side 1 - Front face
	SetupVertexWithNormalGeometry(pVertices, 0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 0.0, 1.0, 0.0, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 0.0, 1.0, 0.0, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 1.0, 1.0, 0.0, 0.0, 0.0, -1.0);
	pFrontBuffer->Unlock();


	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pRightBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pRightBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}
	// Side 2 - Right face
	SetupVertexWithNormalGeometry(pVertices, 0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0);
	pRightBuffer->Unlock();

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pBackBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pBackBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}
	// Side 3 - Rear face
	SetupVertexWithNormalGeometry(pVertices, 0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0);
	pBackBuffer->Unlock();

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pLeftBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pLeftBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}
	// Side 4 - Left face
	SetupVertexWithNormalGeometry(pVertices, 0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 0.0, 0.0, 1.0, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
	pLeftBuffer->Unlock();

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pTopBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pTopBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}
	// Side 5 - Top face
	SetupVertexWithNormalGeometry(pVertices, 0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0);
	pTopBuffer->Unlock();

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pBottomBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pBottomBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}
	// Side 6 - Bottom face
	SetupVertexWithNormalGeometry(pVertices, 0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 1.0, 0.0, 1.0, 0.0, -1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0);
	// Unlock the Cube vertex buffer
	pBottomBuffer->Unlock();

	//create studs
	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(30 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pStudBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer could not be created.
	}
	if (FAILED(pStudBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}

	//faces
	// Side 1 - Front face
	SetupVertexWithNormalGeometry(pVertices, 0, 0.2, 1.0, 0.2, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 1, 0.2, 1.2, 0.2, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 2, 0.8, 1.0, 0.2, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 3, 0.8, 1.0, 0.2, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 4, 0.2, 1.2, 0.2, 0.0, 0.0, -1.0);
	SetupVertexWithNormalGeometry(pVertices, 5, 0.8, 1.2, 0.2, 0.0, 0.0, -1.0);

	// Side 2 - Right face
	SetupVertexWithNormalGeometry(pVertices, 6, 0.8, 1.0, 0.2, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 7, 0.8, 1.2, 0.2, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 8, 0.8, 1.0, 0.8, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 9, 0.8, 1.0, 0.8, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 10, 0.8, 1.2, 0.2, 1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 11, 0.8, 1.2, 0.8, 1.0, 0.0, 0.0);

	// Side 3 - Rear face
	SetupVertexWithNormalGeometry(pVertices, 12, 0.8, 1.0, 0.8, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 13, 0.8, 1.2, 0.8, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 14, 0.2, 1.0, 0.8, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 15, 0.2, 1.0, 0.8, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 16, 0.8, 1.2, 0.8, 0.0, 0.0, 1.0);
	SetupVertexWithNormalGeometry(pVertices, 17, 0.2, 1.2, 0.8, 0.0, 0.0, 1.0);

	//side 4 - left face
	SetupVertexWithNormalGeometry(pVertices, 18, 0.2, 1.0, 0.2, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 19, 0.2, 1.2, 0.8, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 20, 0.2, 1.2, 0.2, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 21, 0.2, 1.0, 0.2, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 22, 0.2, 1.0, 0.8, -1.0, 0.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 23, 0.2, 1.2, 0.8, -1.0, 0.0, 0.0);

	// Side 5 - Top face
	SetupVertexWithNormalGeometry(pVertices, 24, 0.2, 1.2, 0.2, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 25, 0.2, 1.2, 0.8, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 26, 0.8, 1.2, 0.2, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 27, 0.8, 1.2, 0.2, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 28, 0.2, 1.2, 0.8, 0.0, 1.0, 0.0);
	SetupVertexWithNormalGeometry(pVertices, 29, 0.8, 1.2, 0.8, 0.0, 1.0, 0.0);

	// Unlock the Cube vertex buffer
	pStudBuffer->Unlock();

	//set up all the blocks
	SetupLegos();

	return S_OK;
}

// Set up a vertex data.
void SetupVertexWithNormalGeometry(CUSTOMVERTEX* pV, int index,
	float px, float py, float pz,
	float nx, float ny, float nz)
{
	pV[index].position.x = px;	// Vertex co-ordinate.
	pV[index].position.y = py;
	pV[index].position.z = pz;
	pV[index].normal.x = nx;	// Vertex normal.
	pV[index].normal.y = ny;
	pV[index].normal.z = nz;
}

//-----------------------------------------------------------------------------
// Set up the view - the view and projection matrices.
void SetupViewMatrices()
{
	// Set up the view matrix.
	// This defines which way the 'camera' will look at, and which way is up.
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &g_vCamera, &g_vLookat, &vUpVector);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	// Set up the projection matrix.
	// This transforms 2D geometry into a 3D space.
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

//---------------------------------------------------------------------------------

void SetupMaterial(ColourData col)
{
	// Define a material.
	// Reflects only diffuse colour.
	D3DMATERIAL9 Mtl;
	ZeroMemory(&Mtl, sizeof(D3DMATERIAL9));
	Mtl.Diffuse.r = col.r;
	Mtl.Diffuse.g = col.g;
	Mtl.Diffuse.b = col.b;
	Mtl.Diffuse.a = 1.0f;
	g_pd3dDevice->SetMaterial(&Mtl);
}

//---------------------------------------------------------------------------------
void SetupDirectionalLight()
{
	// Define a directional light.
	// Possesses only a diffuse colour.
	D3DLIGHT9 SampleLight;
	ZeroMemory(&SampleLight, sizeof(D3DLIGHT9));
	SampleLight.Type = D3DLIGHT_POINT;

	SampleLight.Diffuse.r = 1.0f;
	SampleLight.Diffuse.g = 1.0f;
	SampleLight.Diffuse.b = 1.0f;

	SampleLight.Position = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	SampleLight.Attenuation0 = 1.0f;
	SampleLight.Attenuation1 = 0.0f;
	SampleLight.Attenuation2 = 0.0f;
	SampleLight.Range = 300.0f;

	// Select and enable the light.
	g_pd3dDevice->SetLight(0, &SampleLight);
	g_pd3dDevice->LightEnable(0, TRUE);
}

//-----------------------------------------------------------------------------
// Render the scene.
void Render()
{
	// Clear the backbuffer to a blue colour, also clear the Z buffer at the same time.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 150), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Define the viewpoint.
		SetupViewMatrices();

		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// Render all the blocks
		for (std::shared_ptr<LegoBlock> &b : g_Blocks)
		{
			SetupMaterial(b->Colour);
			g_pd3dDevice->SetTransform(D3DTS_WORLD, &b->WorldMat);
			//top
			if (!b->TopCovered)
			{
				g_pd3dDevice->SetStreamSource(0, pTopBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

				g_pd3dDevice->SetStreamSource(0, pStudBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 10);
			}
			//bottom
			if (!b->BottomCovered)
			{
				g_pd3dDevice->SetStreamSource(0, pBottomBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			}
			//front
			if (!b->FrontCovered)
			{
				g_pd3dDevice->SetStreamSource(0, pFrontBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			}
			//left
			if (!b->LeftCovered)
			{
				g_pd3dDevice->SetStreamSource(0, pLeftBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			}
			//right
			if (!b->RightCovered)
			{
				g_pd3dDevice->SetStreamSource(0, pRightBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			}
			//back
			if (!b->BackCovered)
			{
				g_pd3dDevice->SetStreamSource(0, pBackBuffer, 0, sizeof(CUSTOMVERTEX));
				g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			}
		}

		// End the scene.
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer to the display.
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

//-----------------------------------------------------------------------------
// The window's message handling function.
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 'w':					//move forward
			g_vCamera.z += 0.2f;
			return 0;
			break;
		case 's':					//move backward
			g_vCamera.z -= 0.2f;
			return 0;
			break;
		case 'a':					//straft left
			g_vCamera.x -= 0.2f;
			return 0;
			break;
		case 'd':					//straft right
			g_vCamera.x += 0.2f;
			return 0;
			break;
		case 'q':					//turn left
			g_vLookat.x -= 0.2f;
			return 0;
			break;
		case 'e':					//turn right
			g_vLookat.x += 0.2f;
			return 0;
			break;
		case 'r':					//move up
			g_vCamera.y += 0.2f;
			return 0;
			break;
		case 'f':					//move down
			g_vCamera.y -= 0.2f;
			return 0;
			break;
		}
		break;

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// WinMain() - The application's entry point.
// This sort of procedure is mostly standard, and could be used in most
// DirectX applications.
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	// Register the window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Basic D3D Example", NULL };
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow("Basic D3D Example", "Directional Lighting Example",
		WS_OVERLAPPEDWINDOW, 100, 100, 1000, 1000,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(SetupD3D(hWnd)))
	{
		// Create the scene geometry
		if (SUCCEEDED(SetupGeometry()))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);

			// Set up the light.
			SetupDirectionalLight();

			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
		}
		CleanUp();
	}

	UnregisterClass("Basic D3D Example", wc.hInstance);
	return 0;
}
