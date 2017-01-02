//-----------------------------------------------------------------------------
// Demonstration of Directional Lighting in Direct3D

#define D3D_DEBUG_INFO

//-----------------------------------------------------------------------------
// Include these files
#include <Windows.h>	// Windows library (for window functions, menus, dialog boxes, etc)
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).
#include "LegoBlock.h"
#include <vector>
#include <memory>
#include "CUSTOMVERTEX.h"
#include "Utils.h"
#include "PatternCreator.h"
#include "MoveableBlock.h"

//-----------------------------------------------------------------------------
// Global variables

LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // The rendering device
std::vector<LegoBlock>  g_Blocks;
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


	return S_OK;
}

//-----------------------------------------------------------------------------
// Release (delete) all the resources used by this program.
// Only release things if they are valid (i.e. have a valid pointer).
// If not, the program will crash at this point.
void CleanUp()
{
	for (LegoBlock &b : g_Blocks)
	{
		if (b.pVertexBuffer != NULL)	b.pVertexBuffer->Release();
	}
	if (g_pd3dDevice != NULL)			g_pd3dDevice->Release();
	if (g_pD3D != NULL)					g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Set up the scene geometry.
// Define a cube, with associated vertex normals.
HRESULT SetupGeometry()
{
	//create the world
	//outer grass
	PatternCreator::AddUniformAmount(g_Blocks, 5, 1, 30, 0, 0, 0, Utils::Green);
	PatternCreator::AddUniformAmount(g_Blocks, 5, 1, 30, 25, 0, 0, Utils::Green);
	PatternCreator::AddUniformAmount(g_Blocks, 20, 1, 5, 5, 0, 0, Utils::Green);
	PatternCreator::AddUniformAmount(g_Blocks, 20, 1, 5, 5, 0, 25, Utils::Green);

	//road
	PatternCreator::AddUniformAmount(g_Blocks, 3, 1, 20, 5, 0, 5, Utils::Grey);
	PatternCreator::AddUniformAmount(g_Blocks, 3, 1, 20, 22, 0, 5, Utils::Grey);
	PatternCreator::AddUniformAmount(g_Blocks, 14, 1, 3, 8, 0, 5, Utils::Grey);
	PatternCreator::AddUniformAmount(g_Blocks, 14, 1, 3, 8, 0, 22, Utils::Grey);

	//center grass and house
	PatternCreator::AddUniformAmount(g_Blocks, 14, 1, 14, 8, 0, 8, Utils::Green);
	PatternCreator::AddUniformAmount(g_Blocks, 3, 2, 4, 10, 1, 10, Utils::Red);

	//create moving block
	MoveableBlock b(6, 1, 6, Utils::Red);
	g_Blocks.push_back(b);




	// Calculate the number of vertices required, and the size of the buffer to hold them.
	int BufferSize = LegoBlock::VertNum * sizeof(CUSTOMVERTEX);
	CUSTOMVERTEX * pVertices;

	//now create a buffer for each block
	for (LegoBlock &b : g_Blocks)
	{
		if (FAILED(g_pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &(b.pVertexBuffer), NULL)))
		{
			return E_FAIL; // if the vertex buffer culd not be created.
		}

		if (FAILED(b.pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0)))
		{
			return E_FAIL;  // if the pointer to the vertex buffer could not be established.
		}

		b.AddVertices(pVertices);

		b.pVertexBuffer->Unlock();
	}	

	return S_OK;
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
	SampleLight.Type = D3DLIGHT_DIRECTIONAL;

	SampleLight.Diffuse.r = 1.0f;
	SampleLight.Diffuse.g = 1.0f;
	SampleLight.Diffuse.b = 1.0f;

	SampleLight.Direction = D3DXVECTOR3(-1, -1, 0); // Light points along -ve X axis.

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
		for (LegoBlock &b : g_Blocks)
		{
			D3DXMATRIX TranslateMat;
			SetupMaterial(b.Colour);
			D3DXMatrixTranslation(&TranslateMat, 0, 0, 0);
			g_pd3dDevice->SetTransform(D3DTS_WORLD, &TranslateMat);
			g_pd3dDevice->SetStreamSource(0, b.pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
			g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, LegoBlock::VertNum / 3);
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
		WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
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
