//-----------------------------------------------------------------------------
// Blank Direct 3D Application

#define D3D_DEBUG_INFO	// Enable debugging information, so the .NET environment can help you.

//-----------------------------------------------------------------------------
// Include these files
#include <Windows.h>	// Windows library (for window functions, menus, dialog boxes, etc)
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).
#include "EasyDirectX.h"

//-----------------------------------------------------------------------------
// WinMain() - The application's entry point.
// This sort of procedure is mostly standard, and could be used in most
// DirectX applications.

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	EasyDirectX edx;
	edx.RegisterWindow();
	edx.CreateApplicationWindow();
	edx.InitializeDirect3D();
	return 0;
}
