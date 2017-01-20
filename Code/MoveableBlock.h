#pragma once
#include "LegoBlock.h"
class MoveableBlock : public LegoBlock
{
public:
	MoveableBlock(float ix, float iy, float iz, LPDIRECT3DTEXTURE9 tex) : LegoBlock(ix, iy, iz, tex){};
	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float zOffset = 0.0f;
	void MoveBlock() { xOffset += 0.1f; }
};

