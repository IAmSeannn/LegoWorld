#pragma once
#include "LegoBlock.h"
#include <vector>
class PatternCreator
{
public:
	PatternCreator();
	~PatternCreator();

	static void AddUniformAmount(std::vector<std::shared_ptr<LegoBlock>>&, int, int, int, float, float, float, LPDIRECT3DTEXTURE9);
};

