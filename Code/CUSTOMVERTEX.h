#pragma once
#include <d3dx9.h>
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	// Position
	D3DXVECTOR3 normal;		// Vertex normal
	DWORD colour;       // The vertex color
};
