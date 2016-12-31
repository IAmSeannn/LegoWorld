#pragma once

#define D3D_DEBUG_INFO	// Enable debugging information, so the .NET environment can help you.

//-----------------------------------------------------------------------------
// Include these files
#include <Windows.h>	// Windows library (for window functions, menus, dialog boxes, etc)
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	float x, y, z;      // X, Y, Z position of the vertex.
	DWORD colour;       // The vertex color
};

// The structure of a vertex in our vertex buffer...
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

class EasyDirectX
{
public:
	EasyDirectX();
	~EasyDirectX();

	//functions from WINMAIN
	void RegisterWindow();
	void CreateApplicationWindow();
	void InitializeDirect3D();


private:
	//vars from WINMAIN
	WNDCLASSEX wc;
	HWND hWnd;
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;

	void Render();
	void CleanUp();
	void SetupViewMatrices();
	HRESULT SetupD3D(HWND hWnd);
	HRESULT SetupGeometry();
};

