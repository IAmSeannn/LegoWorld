#pragma once

#define D3D_DEBUG_INFO	// Enable debugging information, so the .NET environment can help you.

//-----------------------------------------------------------------------------
// Include these files
#include <Windows.h>	// Windows library (for window functions, menus, dialog boxes, etc)
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).



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
	LPDIRECT3D9 D3D;
	LPDIRECT3DDEVICE9 d3dDevice;

	void Render();
	void CleanUp();
	HRESULT SetupD3D(HWND hWnd);
};

