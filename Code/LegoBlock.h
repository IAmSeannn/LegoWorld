#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	// Position
	D3DXVECTOR3 normal;		// Vertex normal
	FLOAT u, v;				// Texture co-ordinates.
};

class LegoBlock
{
public:
	LegoBlock(float ix, float iy, float iz, LPDIRECT3DTEXTURE9 tex) : x(ix), y(iy), z(iz), Texture(tex)
	{
		D3DXMatrixIdentity(&WorldMat);
		D3DXMatrixTranslation(&TranslateMat, ix, iy*1.2f, iz);
		D3DXMatrixScaling(&ScaleMat, 1.0f, 1.2f, 1.0f);
		D3DXMatrixMultiply(&WorldMat, &WorldMat, &ScaleMat);		// First Scale
		D3DXMatrixMultiply(&WorldMat, &WorldMat, &TranslateMat);	// And finally Translate
		TopCovered = false;
		BottomCovered = false;
		RightCovered = false;
		LeftCovered = false;
		FrontCovered = false;
		BackCovered = false;
	};
	~LegoBlock();
	LPDIRECT3DTEXTURE9 Texture;
	D3DXMATRIX WorldMat, TranslateMat, ScaleMat;
	bool TopCovered, BottomCovered, RightCovered, LeftCovered, FrontCovered, BackCovered;
	void SetCovereds(std::vector<std::shared_ptr<LegoBlock>>&);
	float x, y, z;
protected:
	
};

