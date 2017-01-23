#pragma once
#include "LegoBlock.h"
#include <vector>
class PatternCreator
{
public:
	PatternCreator();
	~PatternCreator();

	static void AddUniformAmount(std::vector<std::shared_ptr<LegoBlock>>&, int, int, int, float, float, float, LPDIRECT3DTEXTURE9);
	static void AddFlatPlane(std::vector<std::shared_ptr<LegoBlock>>&, int, int, int, float, float, float, LPDIRECT3DTEXTURE9);
	static void AddWall(std::vector<std::shared_ptr<LegoBlock>>&, int, int, int, float, float, float, LPDIRECT3DTEXTURE9);
	static void AddHouse(std::vector<std::shared_ptr<LegoBlock>>&, float, float, float);
	static void AddBridge(std::vector<std::shared_ptr<LegoBlock>>&, float, float, float);
};

