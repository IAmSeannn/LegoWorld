#include "EasyDirectX.h"
EasyDirectX::EasyDirectX()
{
	camPosX = 0.0f;
	camPosY = 0.0f;
	camPosZ = -35.0f;

	camLookX = 0.0f;
	camLookY = 0.0f;
	camLookZ = 0.0f;
}
EasyDirectX::~EasyDirectX()
{
}

std::shared_ptr<EasyDirectX> EasyDirectX::Current(new EasyDirectX());

//messaging function
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		EasyDirectX::Current->CleanUp();
		PostQuitMessage(0);
		return 0;
	}

	// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 'w':					//move forward
			EasyDirectX::Current->camPosZ += 0.2f;
			return 0;
			break;
		case 's':					//move backward
			EasyDirectX::Current->camPosZ -= 0.2f;
			return 0;
			break;
		case 'a':					//straft left
			EasyDirectX::Current->camPosX -= 0.2f;
			return 0;
			break;
		case 'd':					//straft right
			EasyDirectX::Current->camPosX += 0.2f;
			return 0;
			break;
		case 'q':					//turn left
			EasyDirectX::Current->camLookX -= 0.2f;
			return 0;
			break;
		case 'e':					//turn right
			EasyDirectX::Current->camLookX += 0.2f;
			return 0;
			break;
		case 'r':					//move up
			EasyDirectX::Current->camPosY += 0.2f;
			return 0;
			break;
		case 'f':					//move down
			EasyDirectX::Current->camPosY -= 0.2f;
			return 0;
			break;
		}
		break;

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//-------------------------------------------------------
//Class Functions
void EasyDirectX::RegisterWindow()
{
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "LegoWorld", NULL };
	RegisterClassEx(&wc);
}

void EasyDirectX::CreateApplicationWindow()
{
	hWnd = { CreateWindow("LegoWorld", "LegoWorld - A Place For Lego", WS_OVERLAPPEDWINDOW, 100, 100, 700, 700, GetDesktopWindow(), NULL, wc.hInstance, NULL) };
}

void EasyDirectX::InitializeDirect3D()
{
	// Initialize Direct3D
	if (SUCCEEDED(SetupD3D(hWnd)))
	{
		// Create the scene geometry
		if (SUCCEEDED(SetupGeometry()))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

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

	UnregisterClass("LegoWorld", wc.hInstance);
}

HRESULT EasyDirectX::SetupD3D(HWND hWnd)
{
	// Initialise Direct 3D.
	// Requires a handle to the window in which the graphics will be drawn.

	// Create the D3D object, return failure if this can't be done.
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pd3dDevice)))
	{
		return E_FAIL;
	}

	// Turn on the Z buffer
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Turn off the lighting, as we're using our own vertex colours.
	pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

HRESULT EasyDirectX::SetupGeometry()
{
	//ADD ALL BLOCKS TO BLOCKSVECTOR

	LegoBlock a(0, 0, 0);
	LegoBlock b(3, 3, 3);
	LegoBlock c(0, 3, 0);

	Blocks.push_back(a);
	Blocks.push_back(b);
	Blocks.push_back(c);

	//THEN ADD ALL CONTENTS OF BLOCKS TO pVertices

	// Calculate the number of vertices required, and the size of the buffer to hold them.
	int Vertices = LegoBlock::VertNum * Blocks.size();
	int BufferSize = Vertices * sizeof(CUSTOMVERTEX);

	// Now get Direct3D to create the vertex buffer.
	// The vertex buffer for the rectangle doesn't exist at this point, but the pointer to
	// it does (g_pVertexBuffer)
	if (FAILED(pd3dDevice->CreateVertexBuffer(BufferSize, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVertexBuffer, NULL)))
	{
		return E_FAIL; // if the vertex buffer culd not be created.
	}

	// Fill the buffer with appropriate vertices to describe the rectangle.
	// The rectangle will be made from two triangles...

	// Create a pointer to the first vertex in the buffer
	// Also lock it, so nothing else can touch it while the values are being inserted.
	CUSTOMVERTEX* pVertices;
	if (FAILED(pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;  // if the pointer to the vertex buffer could not be established.
	}

	// Fill the vertex buffers with data...

	std::shared_ptr<int> counter(new int(0));
	for (LegoBlock b : Blocks)
	{
		b.AddVertices(pVertices, counter);
	}


	// Unlock the vertex buffer...
	pVertexBuffer->Unlock();

	return S_OK;
}

void EasyDirectX::Render()
{
	// Clear the backbuffer to a black color
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 150), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(pd3dDevice->BeginScene()))
	{
		// Define the viewpoint.
		SetupViewMatrices();

		// Render the contents of the vertex buffer.
		pd3dDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		// using a D3DPT_TRIANGLELIST primitive - work out nunber of triangles by access block vector
		pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (Blocks.size() * (LegoBlock::VertNum / 3)));

																// End the scene.
		pd3dDevice->EndScene();
	}

	// Present the backbuffer to the display.
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void EasyDirectX::CleanUp()
{
	// Release (delete) all the resources used by this program.
	// Only release things if they are valid (i.e. have a valid pointer).
	// If not, the program will crash at this point.

	if (pVertexBuffer != NULL)	pVertexBuffer->Release();
	if (pd3dDevice != NULL)		pd3dDevice->Release();
	if (pD3D != NULL)			pD3D->Release();
}

void EasyDirectX::SetupViewMatrices()
{
	// Set up the view matrix.
	// This defines which way the 'camera' will look at, and which way is up.
	D3DXVECTOR3 vCamera(camPosX, camPosY, camPosZ);
	D3DXVECTOR3 vLookat(camLookX, camLookY, camLookZ);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &vCamera, &vLookat, &vUpVector);
	pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	// Set up the projection matrix.
	// This transforms 2D geometry into a 3D space.
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

