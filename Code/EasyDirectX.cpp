#include "EasyDirectX.h"

//messaging function
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		// The user has clicked on the 'close' button on the window's title bar.
		// Send a 'WM_QUIT' message to the application to close it down.
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
EasyDirectX::EasyDirectX()
{
}
EasyDirectX::~EasyDirectX()
{
}



void EasyDirectX::RegisterWindow()
{
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "Blank", NULL };
	RegisterClassEx(&wc);
}

void EasyDirectX::CreateApplicationWindow()
{
	hWnd = { CreateWindow("Blank", "Blank Direct3D Application", WS_OVERLAPPEDWINDOW, 100, 100, 700, 700, GetDesktopWindow(), NULL, wc.hInstance, NULL) };
}

void EasyDirectX::InitializeDirect3D()
{
	// Initialize Direct3D
	if (SUCCEEDED(SetupD3D(hWnd)))
	{
		// Show the window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		// Respond to messages until a 'WM_QUIT' message is received.
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

		CleanUp();	// Delete any resources that DX has created/used.
	}

	UnregisterClass("Blank", wc.hInstance);
}

HRESULT EasyDirectX::SetupD3D(HWND hWnd)
{
	// Create the D3D object, return failure if this can't be done.
	if (NULL == (D3D = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3dDevice)))
	{
		return E_FAIL;
	}

	// Turn on the Z buffer
	d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

void EasyDirectX::Render()
{
	DWORD BackgroundColour = 0xF05020;

	// Clear the backbuffer and the z buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BackgroundColour, 1.0f, 0);

	// Begin rendering the scene.
	if (SUCCEEDED(d3dDevice->BeginScene()))
	{
		// ...this is where the graphics would be drawn...

		d3dDevice->EndScene();
	}

	// Present the backbuffer to the display.
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void EasyDirectX::CleanUp()
{
	if (d3dDevice != NULL) d3dDevice->Release();
	if (D3D != NULL)		  D3D->Release();
}

