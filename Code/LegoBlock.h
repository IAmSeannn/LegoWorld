#pragma once
#include "CUSTOMVERTEX.h"
#include <memory>
#include <d3dx9.h>		// Direct 3D library (for all Direct 3D funtions).
#include "ColourData.h"

class LegoBlock
{
public:
	LegoBlock(float ix, float iy, float iz, ColourData col) : x(ix), y(iy), z(iz), Colour(col) {};
	~LegoBlock();
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL; // Buffer to hold vertices
	
	void AddVertices(CUSTOMVERTEX *);
	static const int VertNum = 36;
	ColourData Colour;

protected:
	float x, y, z;
	void AddFaceHorizontal(float, float, float, float, float, float);
	void AddFaceVertical(float, float, float, float, float, float);
	void AddNormal(float, float, float);
	int counter;
	CUSTOMVERTEX * pVertices;
};

