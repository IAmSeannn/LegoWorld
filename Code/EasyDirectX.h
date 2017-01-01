#pragma once

#define D3D_DEBUG_INFO	// Enable debugging information, so the .NET environment can help you.

//-----------------------------------------------------------------------------
// Include these files
#include <Windows.h>	// Windows library (for window functions, menus, dialog boxes, etc)
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).
#include <vector>
#include "LegoBlock.h"
#include "CUSTOMVERTEX.h"
#include <memory>

// The structure of a vertex in our vertex buffer...
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

class EasyDirectX
{
public:
	EasyDirectX();
	~EasyDirectX();

	//functions from WINMAIN
	void RegisterWindow();
	void CreateApplicationWindow();
	void InitializeDirect3D();
	void CleanUp();

	//camera vars
	float camPosX, camPosY, camPosZ, camLookX, camLookY, camLookZ;

	static std::shared_ptr<EasyDirectX> Current;

private:
	//vars from WINMAIN
	WNDCLASSEX wc;
	HWND hWnd;
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;

	std::vector<LegoBlock> Blocks;

	void Render();
	
	void SetupViewMatrices();
	HRESULT SetupD3D(HWND hWnd);
	HRESULT SetupGeometry();
	void SetupMaterial(float r, float g, float b);
	void SetupDirectionalLight();
};

