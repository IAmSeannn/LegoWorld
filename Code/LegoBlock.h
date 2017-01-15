#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).
#include "ColourData.h"

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	// Position
	D3DXVECTOR3 normal;		// Vertex normal
	DWORD colour;       // The vertex color
};

class LegoBlock
{
public:
	LegoBlock(float ix, float iy, float iz, ColourData col) : x(ix), y(iy), z(iz), Colour(col) 
	{
		D3DXMatrixTranslation(&TranslateMat, ix, iy, iz);
		TopCovered = false;
		BottomCovered = false;
		RightCovered = false;
		LeftCovered = false;
		FrontCovered = false;
		BackCovered = false;
	};
	~LegoBlock();
	ColourData Colour;
	D3DXMATRIX TranslateMat;
	bool TopCovered, BottomCovered, RightCovered, LeftCovered, FrontCovered, BackCovered;
	void SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&);

protected:
	float x, y, z;
};

